/* 
 * Copyright (C) 2013  Eric Fiselier
 * 
 * This file is part of elib.
 *
 * elib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * elib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elib.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ELIB_FS_HPPPP
#define ELIB_FS_HPPPP

#include <string>
#include <vector>

namespace elib {

/* fs (filesystem) is a gathering of static methods 
 * to interact with paths (as strings), the filesystem and it's files */
class fs {
private:
    fs();
public:
    /* read a file into dest,
     * return true on success, false otherwise */
    static bool 
    read_file(const std::string & file_name, 
              std::string & dest);
    
    /* write contents to the file at filename 
     * the file must already exist and is entirely overwritten 
     * return true on success, false otherwise */
    static bool 
    write_file(const std::string & file_name, 
               const std::string & contents);
    
    /* create a file with the given contents,
     * no file at file_name should exist 
     * return true on success, false otherwise */
    static bool 
    create_file(const std::string & file_name,
                const std::string & contents);
    
    /* attempt to remove (delete) a file,
     * return true if the file was removed successfully, false otherwise */
    static bool 
    remove_file(const std::string & file_name);
    
    /* return true if the path exists in the filesystem */
    static bool 
    exists(const std::string & path);
    
    /* return true if the path points to a file */
    static bool 
    is_file(const std::string & path);
    
    /* return true if a path points to a directory */
    static bool 
    is_dir(const std::string & path);
    
    /* return the canonical_path for a give path */
    static std::string 
    canonical_path(const std::string & path);
    
    /* make a path canonical */
    static void 
    make_canonical(std::string & path);
    
    /* return true if the path is absolute */
    static bool 
    is_absolute(const std::string & path);
    
    /* return true if the path is relative */
    static bool 
    is_relative(const std::string & path);
    
    /* return true if the path is canonical */
    static bool 
    is_canonical(const std::string & path);
    
    /* search for a file with fname along a search path 
     * return the canonical_path as a match or "" */
    static std::string 
    find(const std::string & fname,
         const std::string & search_path);
    
    /* search for a file with fname along a series of search paths
     * return the canonical_path as a match or "" */
    static std::string 
    find(const std::string & fname,
         const std::vector<std::string> & search_path);
    
    /* search for a file with fname along a series of search paths
     * first from first_search_path, then second_search_path
     * this is for finding system vs non-system headers 
     * return the canonical_path as a match or "" */
    static std::string 
    find(const std::string & fname,
         const std::vector<std::string> & first_search_path,
         const std::vector<std::string> & second_search_path);
    
    /* join two paths */
    static std::string 
    join(const std::string & first, const std::string & second);
    
    /* return the filename portion of a path */
    static std::string 
    filename(const std::string & path);
    
    /* return the parent_path of a path */
    static std::string 
    parent_path(const std::string & path);
    
    /* return the extension on a path */
    static std::string 
    extension(const std::string & path);

private:
    /* internal find implementation */
    static
    void find(const std::string & fname,
              const std::string & search_path,
              std::string & dest);
};
    
} /* namespace elib */
#endif /* ELIB_FS_HPPPP */