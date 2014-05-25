
import sys
import os
import subprocess
import shutil

# Ensure that this is being run on a specific platform
assert sys.platform.startswith('linux') or sys.platform.startswith('darwin')

file_path = os.path.realpath(__file__)
dot_path, file_name = os.path.split(file_path)
# The root enviroment path
env_path = os.path.join(dot_path, "test_env/")
# The root path for writing lists
list_path = os.path.join(dot_path, "test_files")


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
    
    
def create_file(fname):
    fname = sanitize_env_path(fname)
    with open(fname, 'w') as f:
        f.write("Hello World\n")
        
def create_empty_file(fname):
    fname = sanitize_env_path(fname)
    with open(fname, 'w') as f:
        pass
    
    
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
    
    
def create_node(source, mode=0600, device=0):
    source = sanitize_env_path(source)
    os.mknod(source, mode, device)
    
    
def remove(source):
    source = sanitize_env_path(source)
    shutil.rmtree(source, ignore_errors=True)
    
    
def cwd(to):
    to = sanitize_env_path(to)
    d = os.getcwd()
    with open(to, 'w') as f:
        f.write(d + '\n')


def stat(p, to):
    p = sanitize_env_path(p)
    to = sanitize_env_path(to)
    st = os.stat(p)
    _write_stat(st, to)
    
    
def lstat(p, to):
    p = sanitize_env_path(p)
    to = sanitize_env_path(to)
    st = os.lstat(p)
    _write_stat(st, p)
    
    
def _write_stat(st, to):
    with open(to, 'w') as f:
        f.write('st_mode ' + str(st.st_mode) + '\n')
        f.write('st_ino ' + str(st.st_ino) + '\n')
        f.write('st_dev ' + str(st.st_dev) + '\n')
        f.write('st_nlink ' + str(st.st_nlink) + '\n')
        f.write('st_uid ' + str(st.st_uid) + '\n')
        f.write('st_gid ' + str(st.st_gid) + '\n')
        f.write('st_size ' + str(st.st_size) + '\n')
        f.write('st_atime ' + str(int(st.st_atime)) + '\n')
        f.write('st_mtime ' + str(int(st.st_mtime)) + '\n')
        

if __name__ == '__main__':
    command = " ".join(sys.argv[1:])
    try: 
        eval(command)
    except OSError:
        pass
    
    