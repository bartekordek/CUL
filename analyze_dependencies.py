#!/usr/bin/env python3
"""
Analyze Boost dependency graph in CUL project.
This script examines:
1. CMakeLists.txt files to see what's linked
2. C++ source files to see what's actually included
3. Transitive dependencies between Boost libraries
"""

import os
import re
from collections import defaultdict
from pathlib import Path

class BoostDependencyAnalyzer:
    def __init__(self, repo_root):
        self.repo_root = Path(repo_root)
        self.boost_deps = defaultdict(set)  # what each library depends on
        self.boost_includes = defaultdict(set)  # what each library is included by
        self.cmakelists_links = set()  # what's linked in CMakeLists
        self.actual_includes = defaultdict(set)  # actual #includes found
        
    def analyze_cmakelists(self):
        """Parse CMakeLists.txt files to find explicit library dependencies"""
        print("\n[1] Analyzing CMakeLists.txt files...")
        
        # Main CMakeLists.txt
        main_cmake = self.repo_root / "CMakeLists.txt"
        if main_cmake.exists():
            content = main_cmake.read_text()
            # Find all add_subdirectory calls for boost
            boost_libs = re.findall(r'add_subdirectory\s*\(\s*\$\{CUL_DEPS_PATH\}/boost/(\w+)', content)
            for lib in boost_libs:
                self.cmakelists_links.add(lib)
                print(f"  Found in root CMakeLists: boost/{lib}")
        
        # libcul CMakeLists.txt - check what's actually linked
        libcul_cmake = self.repo_root / "libcul" / "CMakeLists.txt"
        if libcul_cmake.exists():
            content = libcul_cmake.read_text()
            # Find target_link_libraries that reference boost_*
            boost_links = re.findall(r'PUBLIC\s+boost_(\w+)|PRIVATE\s+boost_(\w+)', content)
            boost_links = [l[0] or l[1] for l in boost_links]
            print(f"\n  libcul links: {set(boost_links)}")
            for lib in boost_links:
                print(f"    -> boost_{lib}")
    
    def analyze_includes(self):
        """Find actual #include statements for boost libraries"""
        print("\n[2] Analyzing C++ includes...")
        
        include_pattern = re.compile(r'#include\s+[<"]boost/([^/>\"]+)')
        
        # Search all C++ files
        cpp_files = list(self.repo_root.glob("libcul/**/*.cpp")) + \
                    list(self.repo_root.glob("libcul/**/*.hpp")) + \
                    list(self.repo_root.glob("libcul/src/**/*.hpp"))
        
        for cpp_file in cpp_files:
            try:
                content = cpp_file.read_text(encoding='utf-8', errors='ignore')
                matches = include_pattern.findall(content)
                for match in matches:
                    # Extract library name (e.g., "assert.hpp" -> "assert")
                    lib_name = match.split('/')[0].split('.')[0]
                    self.actual_includes[lib_name].add(cpp_file.relative_to(self.repo_root))
                    print(f"  {lib_name:20} <- {cpp_file.relative_to(self.repo_root)}")
            except Exception as e:
                pass
    
    def check_boost_internal_deps(self):
        """Check if boost libraries include each other"""
        print("\n[3] Checking inter-boost dependencies...")
        
        boost_root = self.repo_root / "deps" / "boost"
        if not boost_root.exists():
            print("  (boost deps not available locally)")
            return
        
        for boost_lib_dir in boost_root.iterdir():
            if not boost_lib_dir.is_dir():
                continue
            
            lib_name = boost_lib_dir.name
            # Look for include files
            inc_dir = boost_lib_dir / "include" / "boost"
            if inc_dir.exists():
                for header in inc_dir.rglob("*.hpp"):
                    try:
                        content = header.read_text(encoding='utf-8', errors='ignore')
                        # Find boost includes
                        deps = re.findall(r'#include\s+<boost/(\w+)/', content)
                        for dep in deps:
                            if dep != lib_name:
                                self.boost_deps[lib_name].add(dep)
                    except:
                        pass
    
    def print_report(self):
        """Print comprehensive dependency report"""
        print("\n" + "="*70)
        print("BOOST DEPENDENCY ANALYSIS REPORT")
        print("="*70)
        
        print("\n[LINKED LIBRARIES IN ROOT CMAKELISTS.TXT]")
        for lib in sorted(self.cmakelists_links):
            print(f"  ✓ boost_{lib}")
        
        print(f"\n[LIBRARIES ACTUALLY USED IN CODE]")
        if self.actual_includes:
            for lib in sorted(self.actual_includes.keys()):
                files = sorted(self.actual_includes[lib])
                print(f"  ✓ boost_{lib:20} used in {len(files)} file(s)")
                for f in files[:3]:
                    print(f"      - {f}")
                if len(files) > 3:
                    print(f"      ... and {len(files)-3} more")
        else:
            print("  (none detected)")
        
        print(f"\n[POTENTIALLY UNUSED LIBRARIES]")
        unused = self.cmakelists_links - set(self.actual_includes.keys())
        if unused:
            for lib in sorted(unused):
                print(f"  ⚠ boost_{lib}")
        else:
            print("  (all linked libraries are used)")
        
        print(f"\n[INTER-BOOST DEPENDENCIES]")
        if self.boost_deps:
            for lib in sorted(self.boost_deps.keys()):
                if self.boost_deps[lib]:
                    deps = sorted(self.boost_deps[lib])
                    print(f"  boost_{lib:20} depends on: {', '.join(f'boost_{d}' for d in deps)}")
        else:
            print("  (could not analyze - boost source not available)")
        
        print("\n" + "="*70)
        print("RECOMMENDATIONS:")
        print("="*70)
        
        # Safe to remove?
        print("\nLibraries that can LIKELY be removed:")
        for lib in sorted(self.cmakelists_links):
            if lib not in self.actual_includes:
                # Check if it's a dependency of something else
                is_dependency = any(lib in deps for deps in self.boost_deps.values())
                if not is_dependency:
                    print(f"  ✗ boost_{lib} (not used, not a dependency)")
        
        print("\nLibraries that should be KEPT:")
        for lib in sorted(self.actual_includes.keys()):
            print(f"  ✓ boost_{lib} (directly used)")
        
        print("\nLibraries with TRANSITIVE dependencies:")
        for lib in sorted(self.boost_deps.keys()):
            if self.boost_deps[lib]:
                for dep in sorted(self.boost_deps[lib]):
                    if dep in self.cmakelists_links:
                        print(f"  → boost_{lib} requires boost_{dep}")

def main():
    # Change to repo root
    repo_root = Path(__file__).parent
    
    analyzer = BoostDependencyAnalyzer(repo_root)
    analyzer.analyze_cmakelists()
    analyzer.analyze_includes()
    analyzer.check_boost_internal_deps()
    analyzer.print_report()

if __name__ == "__main__":
    main()
