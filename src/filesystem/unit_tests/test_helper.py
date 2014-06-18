
import sys
import os
import subprocess
import shutil
import socket

# Ensure that this is being run on a specific platform
assert sys.platform.startswith('linux') or sys.platform.startswith('darwin') or \
    sys.platform.startswith('cygwin')

file_path = os.path.realpath(__file__)
dot_path, file_name = os.path.split(file_path)
# The root enviroment path
env_path = os.path.join(dot_path, "dynamic_test_env/")


# Make sure we don't try and write outside of env_path.
# All paths used should be sanitized
def sanitize_env_path(p):
    p = os.path.join(env_path, p)
    p = os.path.realpath(p)
    pre = os.path.commonprefix([env_path, p])
    assert pre == env_path
    return p


"""
Some of the tests restrict permissions to induce failures.
Before we delete the test enviroment, we have to walk it and re-raise the
permissions.
"""
def set_env_perms(root_p):
    root_p = sanitize_env_path(root_p)
    for root,dirs,files in os.walk(root_p):
        for d in dirs:
            d = os.path.join(root,d)
            try:
                os.chmod(d, 0o777)
            except OSError as e:
                pass
        for f in files:
            f = os.path.join(root,f)
            try:
                os.chmod(f, 0o777)
            except OSError as e:
                pass
            

def remove_all_impl_1(root_p):
    for root,dirs,files in os.walk(root_p,topdown=False):
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
        
        
def remove_all_impl_2(root_p):
    for root,dirs,files in os.walk(root_p,topdown=False):
        for f in files:
            os.remove(os.path.join(root,f))           
        for d in dirs:
            os.rmdir(os.path.join(root,d))
        os.rmdir(root)
 
"""
Nothing in pythons os module seems to work for recursive deletion.
Symlinks don't get removed the first time. Sometimes we have to make a second
pass to actually delete the directory.
"""
def remove_all(root_p):
    root_p = sanitize_env_path(root_p)
    remove_all_impl_1(root_p)
    if os.path.exists(root_p):
        remove_all_impl_2(root_p)
        
    
def init(root_p):
    root_p = sanitize_env_path(root_p)
    assert not os.path.exists(root_p)
    os.makedirs(root_p)


def clean(root_p):
    set_env_perms(root_p)
    remove_all(root_p)
    
    
def create_file(fname, size):
    fname = sanitize_env_path(fname)
    with open(fname, 'w') as f:
        for c in ['a'] * size:
            f.write(c)
      
    
def create_dir(dname, mode=0o777):
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
    
    
def create_fifo(source, mode=0o666):
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
       
    