git init
--------------
* local version control
```bash
#add file
git add <filename>
git add -A
#apply changes
git add .
#commit to local repo
git commit -m 'message'
```
* backup local repo to remote repo
```bash
git remote add origin https://github.com/touchpig/reponame.git
```

* push local changes to remote repo
```bash
git push origin master/branch-name
```

* log in
```bash
git config --global user.email "wh19@mail.ustc.edu.cn"
git config --global user.name "toughpig"
```

`git might ignore invisiable files' changes, have to manually "git add .config" for example.`


