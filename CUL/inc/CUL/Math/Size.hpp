#pragma once

namespace CUL
{
	template <typename Type>
	class Size
	{
	public:
		Size()
		{
		}

		Size( const Type width, const Type height ) : mWidth( width ), mHeight( height )
		{
		}

		Size( const Size& size )
		{
			*this = size;
		}

		virtual ~Size()
		{
		}

		Size& operator=( const Size& size )
		{
			if( this != &size )
			{
				mWidth = size.mWidth;
				mHeight = size.mHeight;
			}
			return *this;
		}

		const Type getWidth()const
		{
			return mWidth;
		}

		const Type getHeight()const
		{
			return mHeight;
		}

		void setWidth( const Type width )
		{
			mWidth = width;
		}

		void setHeight( const Type height )
		{
			mHeight = height;
		}

		void setWH( const unsigned int width, const unsigned int height )
		{
			mWidth = width;
			mHeight = height;
		}

		void setWH( const Size& size )
		{
			if( this != &size )
			{
				*this = size;
			}
		}

	protected:
	private:
		Type mWidth = static_cast<Type>(0);
		Type mHeight = static_cast<Type>( 0 );
	};
}