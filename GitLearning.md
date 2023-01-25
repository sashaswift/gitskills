# Git学习

一，创建版本库

* 创建空目录
  
  - 通过mkdir命令建立一个空目录，cd命令打开该目录。
  
  - 通过 git init命令把目录编程Git可管理的仓库（勿手动修改目录下的.git，用ls -ah可显示隐藏的.git）

* 把文件添加到版本库
  
  - git add +文件名，把文件添加到仓库，可多次add不同文件
  
  - git commit -m"(有意义的任何内容)"，把文件提交到仓库，一次可提交多个文件

二, 时间穿梭

* git status 命令，反映仓库当前状态

* git diff + 文件名命令，查看文件修改的具体内容

* 版本回退
  
  - git log 查看历史记录（加上--pretty=oneline，可使信息更精简）
  
  - HEAD 表示当前版本，上一个版本，HEAD^；往上n个版本，HEAD~n;
  
  - git reset --hard HEAD~n 回退n个版本；
  
  - cat +文件名，查看文件具体内容；
  
  - git reset --hard +commit id(可以不写全)，可回到原先的最新版本；
  
  - git reflog 可记录每一次命令；

* 工作区和暂存区
  
  - 工作区：在电脑里可以看到的目录
  
  - 版本库：工作区中的隐藏目录.git，不算工作区
    
    * 暂存区(stage或index)(git add 将文件修改添加到暂存区)；
    
    * master(main)（第一个分支，自动创建）（git commit 将暂存区的所有内容提交到当前的分支）（指向提交）
    
    * HEAD指针，指向master（严格说时指向当前分支）

* 撤销修改
  
  - git checkout  -- 文件名，可丢弃工作区的修改（未存在暂缓区，用git checkout -- 文件名足矣）；
  
  - git reset HEAD +文件名 ，可以把暂存区的修改撤销（unstage),重新放回工作区，再使用git checkout -- 文件名，将工作区的修改删除；

* 删除文件
  
  - rm + 文件名，删除文件管理器（工作区）文件；
  
  - git rm + 文件名    git commit  从版本库中删除文件；
  
  - 版本库中有误删文件，用git checkout -- 文件名，用版本库里的版本替换工作区版本，只能恢复最新版本，会丢失最近一次提交后修改的内容。版本库中没有误删文件，不可复原。

三，远程仓库

* 添加远程仓库（用户本地Git仓库和GitHub仓库之间的传输是通过SSH加密的）
  
  - 创建SSH Key。在用户主目录下,寻找,ssh目录，如果有，则看该目录下有没有id_rsa （私钥，不可泄漏）和 id_rsa.pub（公钥） 文件,如果没有则输入 ssh-keygen -t rsa -C"邮件地址"
  
  - 登录GitHub,从settings中找到”SSH and GPG keys",填上任意Title,在Key文本框里粘贴id_rsa.pub文件得内容，点“add Key"；
  
  - 登陆GitHub，从头像处找到“+”找到” new repository“创建一个新的仓库,在R填入仓库名，保持默认设置，建立Git仓库
  
  - 根据GitHub的提示，在本地的仓库中下运行命令
    
    + git remote add origin git +GitHub的提示，添加后，远程库的名字未origin（默认叫法，可改）
    
    + git push -u origin master命令，可把本地库的内容推送到远程,即把当前分支推送到远程（远程库为空时需要加上-u参数）
  
  - 完成以上步骤后，本地做了提交，就可以通过命令git push origin master 将master分支的最新修改推送至GitHub

* SSH警告（只出现一次）
  
  - 第一次使用Git的clone 或者push命令链接GitHub时，得到警告
  
  - SSH链接在第一次验证时需要确认GitHub的Key指纹信息是否来自GitHub服务器，输入yes回车即可

* 删除远程库
  
  - git remote -v ,可查看远程库信息；
  
  - git remote rm +名字（origin),解除本地与远程的绑定关系，真正删除远程库仍需登录GitHub，在后台页面找到删除按钮删除

* 从远程库克隆
  
  - 在创建远程库时勾选Initialize this repository with a README，GitHub可以自动创建以个README.md文件
  
  - git clone git @github.com:用户名/远程库名.git 克隆一个本地库，用cd  远程库名 ，ls命令即可查看已有README.md

* Git支持多种协议，默认的git://使用ssh,但也可以使用https等其他协议，https速度慢，而且每次推送都必须输入口令，但某些只开放http端口的公司内部就无法使用ssh，只能用https;

四，分支管理

* 创建与合并分支
  
  - 一开始，master分支是条线，master指向最新提交，HEAD指向master，从而确定当前分支及当前分支的提交点，每次提交，master分支都会向前移动一步
  
  - 创建dev分支时，Git新建了一个指针叫dev，指向master相同的提交，再把HEAD指向dev，就表示当前分支在dev上，此后对工作区的修改和提交就是针对dev分支，新提交一次后，dev向前移动一步，master指针不变。
    
    + git checkout -b +分支名，创建并切换分支（相当于 git branch +分支名，和 git checkout + 分支名）
    
    + git branch ，查看当前分支（当前分支前会有*号）
    
    + git checkout +分支名 ，切换分支
    
    + git switch -c +分支名，创建并切换分支
    
    + git switch +分支名，切换分支
  
  - 合并分支：以dev分支为例，可直接把master直接指向dev的当前提交，合并完成后，可以通过删除dev指针删除dev分支
    
    + git merge +分支名，将该分支合并到master分支上（页面的Fast-forward 表示快进模式）
    
    + git branch -d +分支名，可删除该分支（删除之前先将当前分支转换成master)

* 解决冲突
  
  + 当Git无法快速合成分支（如各分支皆有了修改提交），只能将各自修改合并起来，从而引发冲突。
  
  + 解决冲突步骤：
    
    + 冲突后，使用git status可以告知冲突文件
    
    + 通过cat +文件名 直接查看冲突文件，Git 用<<<<<,=====,>>>>>>标记出不同分支的内容
    
    + 解决冲突，手动修改编辑冲突文件内容使其成为我们希望的内容，再提交，合并完成
    
    + 用git log --graph --pretty=oneline --abbrev-commit 查看分支的合并情况；

* 分支管理策略
  
  - 通常合并分支所使用的Fast forward模式会使得删除分支后丢失分支信息（分支历史上看不出有分支），强制禁用该模式，Git就会在merge时生成一个新的commit,使得分支历史上可以查询到分支信息
  
  - 具体操作：
    
    + 将分支切换回master;
    
    + 使用 git merge --no-ff -m"XXX" git+分支名,--no-ff参数表示禁用Fast forward,-m把commit 描述写上表示创建一个新的commit
    
    + 用git log --graph --pretty=oneline --abbrev-commit查看分支历史
  
  - 分支管理基本原则：
    
    + master分支非常稳定，仅用来发布新版本，平时不能在上面干活
    
    + 干活都在dev分支上（不稳定）,每个人将自己的分支->dev->master
- Bug 分支
  
  - 每个bug都可以通过一个新的临时分支修复，修复后合并分支，最后将临时分支删除
  
  - 当手头工作未完成，而需要修复bug时，可以先将工作现场git stash,储存起来，再修复bug
  
  - 修复bug:
    
    + 首先确定在哪个分支上修复bug,在该分支上建立临时分支
    
    + 修复bug,并在临时分支上提交；
    
    + 切换到修复分支，将两分支合并，删除临时分支
  
  - 修复一个分支后，其它存在bug的分支：
    
    - 确定修改分支，将该分支转换为当前分支
    + 复制修复提交时的commit id
    
    + 在修改分支上，使用git cherry-pick +commit id,复制特定的提交到当前分支，Git自动给修改分支做了一次提交，与先前的commit不同，改动相同。
  
  - 继续工作
    
    + 回到工作的分支；
    
    + 使用git stash list 查看工作现场
    
    + git stash pop 回复并删除stash内容（等同git stash apply(恢复stash）+ git stash drop(删除stash) )

- Feature 分支
  
  - 软件开发时，每添加一个新功能，最好新建分支，在上面进行开发，完成后，合并，最后删除该分支
  
  - 若提交新功能的分支需要删除，则在合并前，使用git branch -D +分支名可以强行删除，修改信息也会丢失

- 多人协作
  
  - 当从远程仓库克隆时，Git自动把本地的master分支与远程的master分支对应了起来，而且，远程仓库的默认名称是origin,可以用git remote查看远程仓库的信息
  
  - git remote -v可以显示更详细的信息，比如可以抓取和推送origin的地址。
  
  - 推送分支
    
    + 将该分支上所有的本地提交推送到远程库上。
    
    + git push origin +分支名，推送分支
    
    + master,dev分支需要与远程同步
    
    + bug 分支有需求可以推送到远程
    
    + feature分支是否推送决于合作要求
  
  - 抓取分支
    
    + 当从远程库clone时，默认只能看到本地的master分支，若合作时，合作方都建立dev分支对同一个文件进行修改，并推送，则推送失败。
    
    + git pull 把最新提交从origin/dev 抓取下来，解决冲突后，在本地合并再推送（若提示no tracking information,先git branch --set-upstream-to=origin/dev dev，指定本地dev与远程origin/dev分支的链接，再git pull)
    
    + git pull后合并有冲突，需要手动解决，解决方法和分支管理中的解决冲突完全一样，解决后，提交，再push

- Rebase
  
  - 很多人在同一个分支上协作时很容易出现冲突，即使没有冲突，后push的工作也必须先git pull，在本地合并，然后才能push成功,导致分支看起来十分凌乱，rebase操作可以将Git提交历史变成一条直线
  
  - 在发现有人先提交推送了远程分支，先pull，使用git log --graph --pretty=oneline --abbrev-commit查看会发现提交历史分叉。
    
    + 输入git rebase，把分叉的提交历史“整理”成了一条直线，最终提交的内容一致，但本地的分叉提交已经被修改过了
    
    + 输入 git log --graph --pretty=oneline --abbrev-commit查看就是一条直线了
    
    + push操作将本地分支推送到远程，再使用git log --graph --pretty=oneline --abbrev-commit查看效果

五，标签管理

- 发布一个版本时，通常先在版本库中打一个标签（tag),就唯一确定打标签时刻的版本。取某个标签的版本，就是将打标签的时刻的历史版本取出来。标签是版本库的一个快照（实质上是指向某个commit指针，但不可移动，比起commit id标签更容易记住）

- 创建和删除标签都是瞬间的；

- 创建标签
  
  - 首先，切换到需要打标签的分支上（但如果其他分支上也有打了标签的commit,两个分支都可以看到标签）
  - git tag +标签名，打一个新标签，默认打在最新提交的commit
  - git tag 可查看所有标签（标签按字母排序，非时间顺序）
  - 如果将标签打在最新提交的commit 之前的commit，则可以通过git log --pretty=oneline --abbrev-commit查看历史提交的commit id  然后用 git tag +标签名 +对应的commit id
  - git show +标签名，可查看标签信息
  - git tag -a +标签名  -m"说明文字" +commit id,创建有说明的标签

- 操作标签
  
  + git tag -d +标签名,可删除本地该标签
  
  + 创建的标签只存储在本地，不会自动推送到远程，打错的标签可以在本地安全删除
  
  + git push origin +标签名，将标签名推送到远程
  
  + git push origin --tags，一次性推送所有的本地尚未推送的标签
  
  + 如果标签已推送到远程
    
    + 删除本地的标签
    
    + git push origin :refs/tags/标签名 ，远程删除标签

六，自定义GitHub

* 忽略特殊文件
  
  - 在Git工作区的根目录创建一个特殊的.gitignore文件，然后把要忽略的文件名填进去，即可忽略
  
  - 忽略文件的原则：
    
    + 操作系统自动生成的文件，比如缩略图等
    
    + 编译生成的中间文件、可执行文件等（另一个文件自动生成的文件）没必要放进版本库
    
    + 带有敏感信息的配置文件
  
  - 被.gitignore忽略的文件无法直接被添加到Git，使用git add -f +文件名 即可强制将忽略的文件直接添加到Git 
  
  - git check-ignore -v +添加有问题的文件，可以查看.gitignore哪个规则有问题
  
  - 把指定文件名排除到.gitignore规则之外的写法：！+文件名
  
  - .gitignore文件本身要放进版本库，并且可以对`.gitignore做版本管理

* 配置别名：git config --global alias. +别名 +命令名（‘命令名’），将命令名修改成别名，--global是全局参数，即命令对本电脑的所有Git仓库下都有用，如果不加则只针对当前仓库

* 配置文件：
  
  - 每个仓库的Git配置文件都放在.git/config文件中，用cat +.git/config 命令后，别名在[alias]后面
  
  - 当前用户的Git配置的文件放在用户主目录下的隐藏文件.gitconfig,配置别名也可以直接修改这个文件，如果改错了，可以删掉文件重新通过命令配置。

* 搭建Git 服务器
  
  - 需要准备一台运行Linux的机器
  
  - 创建拥有sudo权限的用户账号
  
  - sudo apt-get install git,安装git
  
  - sudo adduser git ,创建一个git 用户
  
  - 收集所有需要登录的用户的公钥，即id_rsa.pub文件，把所有公钥导入到/home/git/.ssh/authorized_keys文件里，一行一个，创建证书登录
  
  - 初始化Git仓库：
    
    + 先选定一个目录作为Git仓库，在该目录下输入sudo git init --bare +.git文件名，创建一个裸仓库（没有工作区）
    
    + sudo chown -R git :git +.git 文件名，把owner改为git
  
  - 禁用shell登录
    
    + 出于安全考虑，创建的git用户不允许登录shell，可以通过编辑/etc/passwd文件完成
    
    + 找到类似：
      
          git:x:1001:1001:,,,:/home/git:/bin/bash
    
    + 改为：
      
          git:x:1001:1001:,,,:/home/git:/usr/bin/git-shell
  
  - 克隆远程仓库：git clone git @server: 目录地址

* 
  
  
