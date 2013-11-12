import sys
import os
import subprocess
import shutil

dot_path, file_name = os.path.split(os.path.realpath(__file__))
file_path = os.path.join(dot_path, file_name)

def read_list(filename):
  if not os.path.exists(filename):
    filename = os.path.join(dot_path, filename)
  with open(filename, 'r') as f:
    lines = [line.strip() for line in f]
    return lines

def write_list(l, filename):
  if not os.path.isabs(filename):
    filename = os.path.join(dot_path, filename)
  with open(filename, 'w') as f:
    for ll in l:
      f.write(ll)
      f.write("\n")
      
def write_list_abs(l, filename):
  test_env = os.path.join(dot_path, "test_env")
  l = [ os.path.join(test_env, p) for p in l]
  write_list(l, filename)

def call_shell(cmd):
  try:
    subprocess.call(cmd, shell=True)
  except subprocess.CalledProcessError as er:
    print(er)
    

  


"""
  setup and takedown for query tests
"""

relative_paths = ['test_env', './test_env', '../fs/test_env', 
                  '././test_env', 'test_env/dir1', './test_env/dir1',
                  './test_env/../test_env/dir1']
dne_paths = ["dne", "dir1/dne", "cfile1/dne"]

directories = ["dir1", "dir1/dir2", "dir2", "dir2/dir1", "dir2/dir1/dir1"]
character_files = ["/dev/null", "/dev/zero"]
block_files = ["/dev/sda"]
regular_files = ["rfile1", "rfile2", "dir1/rfile1", "dir2/dir1/rfile1"]
fifo_files = ["fifo1", "dir1/fifo1", "dir2/fifo1", "dir2/dir1/fifo1"]

symlink_from = ["dir1", character_files[0], block_files[0], "dir1/rfile1"]
symlink_to = ["sym_dir1", "sym_cfile1", "sym_bfile1", "dir1/sym_rfile1"]

empty_files = ["empty1", "dir1/empty1", "dir2/dir1/empty1"]
non_empty_files = [regular_files[0], regular_files[1], regular_files[2]]

def init_filesystem():
  env_path = os.path.join(dot_path, "test_env")
  if not os.path.exists(env_path):
    os.mkdir(env_path)
  init_path_files()
  init_query_files()
  
def init_path_files():
  write_list(relative_paths, "test_files/relative_paths")
  ap = [ os.path.join(dot_path, p) for p in relative_paths]
  write_list(ap, "test_files/absolute_paths")
  cp = [ os.path.abspath(p) for p in relative_paths]
  write_list(cp, "test_files/canonical_paths")
  

def init_query_files():

  env_path = os.path.join(dot_path, "test_env")
  
  write_list_abs(dne_paths, "test_files/dne_paths")
  
  for d in directories:
    abs_path = os.path.join(env_path, d)
    if not os.path.exists(abs_path):
      os.makedirs(abs_path)
  write_list_abs(directories, "test_files/directories")
  
  
  write_list_abs(character_files, "test_files/character_files")
  
  write_list(block_files, "test_files/block_files")
  
  for fn in regular_files:
    abs_path = os.path.join(env_path, fn)
    with open(abs_path, 'w') as f:
      f.write(fn + "\n")
  write_list_abs(regular_files, "test_files/regular_files")
  
  for fn in fifo_files:
    abs_path = os.path.join(env_path, fn)
    call_shell("mknod " + abs_path + " p")
  write_list_abs(fifo_files, "test_files/fifo_files")
  
  for i in range(0, len(symlink_from)):
    from_path = os.path.join(env_path, symlink_from[i])
    to_path = os.path.join(env_path, symlink_to[i])
    if not os.path.exists(to_path):
      os.symlink(from_path, to_path)
  write_list_abs(symlink_from, "test_files/symlink_from")
  write_list_abs(symlink_to, "test_files/symlink_to")
  
  for fn in empty_files:
    abs_path = os.path.join(env_path, fn)
    call_shell("touch " + abs_path)
  write_list_abs(empty_files, "test_files/empty_files")
  
  for fn in non_empty_files:
    abs_path = os.path.join(env_path, fn)
    with open(abs_path, 'w') as f:
      f.write(fn)
  write_list_abs(non_empty_files, "test_files/non_empty_files")
  
  
def clean_filesystem():
  env_path = os.path.join(dot_path, "test_env")
  list_path = os.path.join(dot_path, "test_files")
  
  shutil.rmtree(env_path)
  
  created_lists = ["relative_paths", "directories", "character_files", 
                   "block_files", "regular_files", "fifo_files", "symlink_to",
                   "symlink_from", "empty_files", "non_empty_files",
                   "absolute_paths", "canonical_paths", "dne_paths"]
  
  for fn in created_lists:
    abs_path = os.path.join(list_path, fn)
    if os.path.exists(abs_path):
      os.remove(abs_path)
  
    
  


if __name__ == '__main__':
  command = " ".join(sys.argv[1:])
  assert os.getcwd() == dot_path, "wrong cwd"
  eval(command)