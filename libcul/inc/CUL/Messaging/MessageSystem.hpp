#pragma once

#include <CUL/String/StringWrapper.hpp>
#include <CUL/GenericUtils/NonCopyable.hpp>
#include <CUL/STL_IMPORTS/STD_atomic.hpp>
#include <CUL/STL_IMPORTS/STD_condition_variable.hpp>
#include <CUL/STL_IMPORTS/STD_functional.hpp>
#include <CUL/STL_IMPORTS/STD_future.hpp>
#include <CUL/STL_IMPORTS/STD_mutex.hpp>
#include <CUL/STL_IMPORTS/STD_queue.hpp>
#include <CUL/STL_IMPORTS/STD_unordered_map.hpp>
#include <CUL/STL_IMPORTS/STD_vector.hpp>

namespace CUL
{
template <class MessageType>
class MessageSystem
{
public:
    static MessageSystem& getInstance()
    {
        static MessageSystem s_instance;
        return s_instance;
    }

    template <typename TObject>
    void registerHandler( void ( TObject::*function )( const MessageType& ),
                          TObject* object )
    {
        std::lock_guard<std::mutex> locker( m_handlersMtx );

        m_handlers.emplace( object,
                            [object, function]( const MessageType& message )
                            {
                                ( object->*function )( message );
                            } );
    }

    void removeHandler( void* inObject )
    {
        std::lock_guard<std::mutex> locker( m_handlersMtx );
        m_handlers.erase( inObject );
    }

    void send( const MessageType& message )
    {
        {
            std::lock_guard locker( m_messagesMtx );
            m_messages.push( message );
        }

        m_messagesCv.notify_one();
    }

private:
    MessageSystem()
    {
        m_messageThread =
            std::async( std::launch::async, &MessageSystem::processMessages, this );
    }

    void processMessages()
    {
        while( !m_stop )
        {
            MessageType message;

            {
                std::unique_lock locker( m_messagesMtx );

                m_messagesCv.wait( locker,
                                   [this]
                                   {
                                       return !m_messages.empty() || m_stop;
                                   } );

                if( m_stop )
                {
                    return;
                }

                message = std::move( m_messages.front() );
                m_messages.pop();
            }

            sendImmediate( message );
        }
    }

    void sendImmediate( const MessageType& inMessage )
    {
        std::vector<std::function<void( const MessageType& )>> handlers;

        {
            std::lock_guard<std::mutex> locker( m_handlersMtx );

            handlers.reserve( m_handlers.size() );

            for( const auto& handler : m_handlers )
            {
                handlers.push_back( handler.second );
            }
        }

        for( const auto& handler : handlers )
        {
            handler( inMessage );
        }
    }

    ~MessageSystem()
    {
        m_stop = true;
        m_messagesCv.notify_one();
        m_messageThread.wait();
    }

    CUL_NONCOPYABLE( MessageSystem );

    std::atomic_bool m_stop{ false };

    std::future<void> m_messageThread;

    std::queue<MessageType> m_messages;
    std::mutex m_messagesMtx;
    std::condition_variable m_messagesCv;

    std::unordered_map<void*, std::function<void( const MessageType& )>> m_handlers;
    std::mutex m_handlersMtx;
};
}  // namespace CUL