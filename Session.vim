let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +8 ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies/CMakeLists.txt
badd +1 ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies/deps/deps_helper.cmake
badd +11 ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies/deps/ext.cmake
badd +1 ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies/deps/CPM.cmake
badd +8 ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies/src/main.cpp
badd +3 ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies/src/shaders/fragment.glsl
badd +1 ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies/src/shaders/vertex.glsl
argglobal
%argdel
edit ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies/deps/ext.cmake
argglobal
balt ~/Documents/kody/Tymek/kody/Space_Gaming_Zombies/deps/deps_helper.cmake
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 11 - ((10 * winheight(0) + 22) / 45)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 11
normal! 034|
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
