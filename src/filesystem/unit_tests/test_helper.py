
import sys
import os
import subprocess
import shutil
import socket

# Ensure that this is being run on a specific platform
assert sys.platform.startswith('linux') or sys.platform.startswith('darwin')

file_path = os.path.realpath(__file__)
dot_path, file_name = os.path.split(file_path)
# The root enviroment path
env_path = os.path.join(dot_path, "test_env/")
# The root path for writing lists
list_path = os.path.join(dot_path, "test_files")


# Make sure we don't try and write outside of env_path.
# All paths used should be sanitized
def sanitize_env_path(p):
    p = os.path.join(env_path, p)
    p = os.path.realpath(p)
    pre = os.path.commonprefix([env_path, p])
    assert pre == env_path
    return p
    
    
def init():
    os.mkdir(env_path)


def clean():
    shutil.rmtree(env_path, ignore_errors=True)
    
    
def create_file(fname, size):
    fname = sanitize_env_path(fname)
    with open(fname, 'w') as f:
        for c in ['a'] * size:
            f.write(c)
      
    
def create_dir(dname, mode=0777):
    dname = sanitize_env_path(dname)
    os.mkdir(dname, mode)
    
    
def create_dirs(dname, mode=0777):
    dname = sanitize_env_path(dname)
    os.makedirs(dname,mode)
    
    
def create_symlink(source, link):
    source = sanitize_env_path(source)
    link = sanitize_env_path(link)
    os.symlink(source, link)
    
    
def create_hardlink(source, link):
    source = sanitize_env_path(source)
    link = sanitize_env_path(link)
    os.link(source, link)
    
    
def create_fifo(source, mode=0666):
    source = sanitize_env_path(source)
    os.mkfifo(source, mode)

    
def create_socket(source):
    source = sanitize_env_path(source)
    s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    s.bind(source)
    
def remove(source):
    source = sanitize_env_path(source)
    shutil.rmtree(source, ignore_errors=True)
    
    
def cwd(to):
    to = sanitize_env_path(to)
    d = os.getcwd()
    with open(to, 'w') as f:
        f.write(d + '\n')
        

if __name__ == '__main__':
    command = " ".join(sys.argv[1:])
    try: 
        eval(command)
    except OSError:
        pass
    
    