#!/usr/bin/python

import os.path as path

debug = True

out_dir = path.join(path.dirname(path.realpath(__file__)), "output")

pp_arity_limit = 15
pp_arithmetic_limit = 256


def status(s):
  if debug:
    print(s)


def join_dir(p):
  return path.join(out_dir, p)


def write_header(fname, s):
  s = s[1:]
  with open( join_dir(fname), 'w') as f:
    f.write(s)
    f.close()
    status('wrote file: "%s"' % (join_dir(fname),))
    return True
  status('failed to write: "%s"' % (join_dir(fname),))
  return False


def main():
  print("Config Values: ")
  print('  out_dir = "%s"' % (out_dir,))
  print('    is_dir = %s' % (str(path.isdir(out_dir)),))
  print('  pp_arity_limit = %i\n  pp_arithmetic_limit = %i' 
        % (pp_arity_limit, pp_arithmetic_limit))
  
  
if __name__ == '__main__':
  main()