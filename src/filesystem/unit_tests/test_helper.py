
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

def set_env_perms():
    for root,dirs,files in os.walk(env_path):
        for d in dirs:
            d = os.path.join(root,d)
            try:
                os.chmod(d, 0777)
            except OSError as e:
                pass
        for f in files:
            f = os.path.join(root,f)
            try:
                os.chmod(f, 0777)
            except OSError as e:
                pass
                
def remove_all_impl_1():
    for root,dirs,files in os.walk(env_path,topdown=False):
        for f in files:
            try:
                os.remove(os.path.join(root,f))
            except OSError:
                pass
        for d in dirs:
            try:
                os.rmdir(os.path.join(root,d))
            except OSError as e:
                pass
        try:
            os.rmdir(root)
        except OSError:
            pass
        
def remove_all_impl_2():
    for root,dirs,files in os.walk(env_path,topdown=False):
        for f in files:
            os.remove(os.path.join(root,f))           
        for d in dirs:
            os.rmdir(os.path.join(root,d))
        os.rmdir(root)
 

def remove_all():
    remove_all_impl_1()
    if os.path.exists(env_path):
        remove_all_impl_2()
        
    
def init():
    if os.path.exists(env_path):
        remove_all()
    os.mkdir(env_path)


def clean():
    set_env_perms()
    remove_all()
    
    
def create_file(fname, size):
    fname = sanitize_env_path(fname)
    with open(fname, 'w') as f:
        for c in ['a'] * size:
            f.write(c)
      
    
def create_dir(dname, mode=0777):
    dname = sanitize_env_path(dname)
    os.mkdir(dname, mode)
    
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
    

if __name__ == '__main__':
    command = " ".join(sys.argv[1:])
    eval(command)
    sys.exit(0)
   

    
    