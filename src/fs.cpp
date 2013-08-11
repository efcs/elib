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
#include "elib/fs.h"

#include <fstream>

#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

namespace elib {

bool
fs::read_file(const std::string & file_name, std::string & contents)
{
    if (! is_file(file_name))
        return false;
    
    std::ifstream in;
    in.open(file_name, std::ios::in);
    
    if (! in.good())
        return false;
    
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    
    assert(in.good());
    in.close();
    
    return true;
}


bool
fs::write_file(const std::string & file_name,
               const std::string & contents)
{
    if (! is_file(file_name))
        return false;
    
    std::ofstream out;
    out.open(file_name, std::ios::out);
    
    if (! out.good())
        return false;
    
    out << contents;
    
    assert(out.good());
    out.close();
    
    return true;
}

bool
fs::create_file(const std::string & file_name,
                const std::string & contents)
{
    if (exists(file_name))
        return false;
    
    std::ofstream out;
    out.open(file_name, std::ios::out);
    if (! out.good())
        return false;
    
    out.close();
    
    bool ret = write_file(file_name, contents);
    
    if (! ret)
        remove_file(file_name);
    
    return ret;
}

bool
fs::remove_file(const std::string & file_name)
{
    if (! is_file(file_name))
        return false;
    
    bfs::path p(file_name);
    return bfs::remove(p);
}

bool
fs::exists(const std::string & path)
{
    bfs::path p(path);
    return bfs::exists(p);
}

bool
fs::is_file(const std::string & path)
{
    bfs::path p(path);
    return bfs::is_regular_file(p);
}

bool
fs::is_dir(const std::string & path)
{
    bfs::path p(path);
    return bfs::is_directory(p);
}


std::string
fs::canonical_path(const std::string & path)
{
    bfs::path p(path);
    
    if (! exists(path) )
        return "";
    
    return bfs::canonical(p).string();
}

void
fs::make_canonical(std::string & path)
{
    auto tmp = canonical_path(path);
    path = tmp;
}

bool
fs::is_absolute(const std::string & path)
{
    bfs::path p(path);
    return p.is_absolute();
}

bool
fs::is_relative(const std::string & path)
{
    bfs::path p(path);
    return p.is_relative();
}

bool
fs::is_canonical(const std::string & path)
{
    if (path.size() == 0)
        return false;
    
    auto str = canonical_path(path);
    
    return (str == path);
}

std::string
fs::find(const std::string & fname,
         const std::string & search_path)
{
    std::string tmp;
    find(fname, search_path, tmp);
    return tmp;
}


std::string 
fs::find(const std::string & fname,
         const std::vector<std::string> & search_paths)
{
    std::string tmp;
    for (auto &s_path : search_paths) {
        find(fname, s_path, tmp);
        if (tmp.size() != 0)
            return tmp;
    }
    
    assert(tmp.size() == 0);
    return tmp;
}

std::string
fs::find(const std::string & fname,
         const std::vector<std::string> & first_search_paths,
         const std::vector<std::string> & second_search_paths)
{
    std::string tmp = find(fname, first_search_paths);
    
    if (tmp.size() != 0)
        return tmp;
    
    return find(fname, second_search_paths);
}


std::string
fs::join(const std::string & first, const std::string & second)
{
    bfs::path first_path(first);
    first_path /= second;
    return first_path.string();
}

std::string
fs::filename(const std::string & path)
{
    bfs::path p(path);
    return p.filename().string();
}

std::string
fs::parent_path(const std::string & path)
{
    bfs::path p(path);
    auto tmp = p.parent_path();
    return tmp.string();
}

std::string
fs::extension(const std::string & path)
{
    bfs::path p(path);
    auto tmp = p.extension();
    return tmp.string();
}

////////////////////////////////////////////////////////////////////////////////
//                          fs private methods                                //
////////////////////////////////////////////////////////////////////////////////

void
fs::find(const std::string & fname,
         const std::string & search_path,
         std::string & dest) 
{
    if (! is_dir(search_path))
        return;

    bfs::path spath(fs::canonical_path(search_path));

    spath /= fname;
    
    if (is_file(spath.string()))
        dest = spath.string();
}

} /* namespace elib */