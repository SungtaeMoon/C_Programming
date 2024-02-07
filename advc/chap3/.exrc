if &cp | set nocp | endif
map .th : TOhtml
map .ti i	w
map .k O
map .j o
let s:cpo_save=&cpo
set cpo&vim
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
nmap mke :!%< >                                       "프로그램 실행
nmap mka :w :!rm err :!compile %< :!cat err   "프로그램 컴파일
map <F3> : !./%<
map <F2> : !gcc -W -Wall -o %< %
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=indent,eol,start
set cindent
set display=truncate
set expandtab
set fileencodings=utf-8,cp949
set guicursor=n-v-c:block,o:hor50,i-ci:hor15,r-cr:hor30,sm:block,a:blinkon0
set helplang=ko
set history=1000
set hlsearch
set incsearch
set langnoremap
set nolangremap
set laststatus=2
set matchpairs=(:),{:},[:],<:>
set nrformats=bin,hex
set pastetoggle=<Insert>
set ruler
set scrolloff=5
set shiftwidth=4
set showmatch
set smartcase
set smartindent
set softtabstop=4
set statusline=%<%F%h%m%r%h%w%y\ %{strftime(\"%Y/%m/%d-%H:%M\")}%=\ col:%c%V\ ascii:%b\ pos:%o\ lin:%l,%L\ %P
set tabstop=4
set ttimeout
set ttimeoutlen=100
set wildmenu
" vim: set ft=vim :
