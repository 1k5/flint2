
from __future__ import print_function

from os import chdir, walk
from os.path import join, dirname, normpath, split, splitext
import shutil
import string
import copy
import subprocess
import code
import sys
import re

script_dir = dirname(__file__)
chdir(script_dir)
exe_dir = normpath(join(script_dir, '..\\tests\\x64\\Release'))
vcx_dir = normpath(join(script_dir, '..\\flint-tests'))

def split_pnx(p):
  h, t = split(p)
  n, x = splitext(t)
  if x == '.filters':
    n, _ = splitext(x)
  return (h, n, x)

vcd, vcp, vcf = [], [], []
for root, dirs, files in walk(vcx_dir):
  if root.endswith('win32') or root.endswith('x64'):
    for x in list(dirs):
      dirs.remove(x)
  for x in dirs:
    if x not in ('win32', 'x64'):
      vcd.append(x)
  for z in files:
    h, t = splitext(z)
    if t == '.vcxproj':
      vcp.append(h)
    if t == '.filters':
      vcf.append(splitext(h)[0])

if not (len(vcd) == len(vcp) == len(vcf)):
  print('warning: some tests may be missing or corrupted')
  print(len(vcd), len(vcp), len(vcf))
  
exd, exe, pdb, ext = [], [], [], []
for root, dirs, files in walk(exe_dir):
  for x in dirs:
    exd.append(x)
  for x in files:
    h, t = splitext(x)
    if t == '.exe':
      exe.append(h)
    elif t == '.pdb':
      pdb.append(h)
    else:
      ext.append(x)

if len(ext) > 1:
  print('warning: unexpected files in binary test directory', len(ext))
if len(exe) > len(pdb):
  print('warning: some debug files are missing', len(exe), len(pdb))
elif len(exe) < len(pdb):
  print('warning: some test binaries may be missing', len(exe), len(pdb))

build_fail = 0
run_ok = 0
run_fail = 0
for i in exe:
# if i in exe:
  ef = join(exe_dir, i) + '.exe'
  try:
    prc = subprocess.Popen( ef, stdout = subprocess.PIPE,
      stderr = subprocess.STDOUT, creationflags = 0x08000000 )
  except Exception as str:
    print(i, ': ERROR (', str, ')')
    run_fail += 1
    continue
  output = prc.communicate()[0]
  if prc.returncode:
    print('ERROR {}'.format(prc.returncode), end=' ')
    run_fail += 1
  else:
    run_ok += 1
  if output:
    print(output.decode().replace('\n', ''))
  else:
    print()
#  else:
#    print("Build failure for {0}".format(i))
#    build_fail += 1
print(build_fail + run_ok + run_fail, "tests:")
if build_fail > 0:
  print("\t{0} failed to build".format(build_fail))
if run_ok > 0:
  print("\t{0} ran correctly".format(run_ok))
if run_fail > 0:
  print("\t{0} failed".format(run_fail))
if len(sys.argv) == 1:
  try:
    input(".. completed - press ENTER")
  except:
    pass
else:
  sys.exit(build_fail + run_fail)
