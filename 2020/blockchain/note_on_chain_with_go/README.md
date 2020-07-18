# name
Golang开发一个增改查的Dapp记事本

# Description
[用Golang开发一个增改查的Dapp记事本](https://blog.csdn.net/qq624202120/article/details/107128214)

# Usage

修改 service/NoteService.go 的合约相关配置
| 名称              |                              当前值                              |   作用   |
| ----------------- | :--------------------------------------------------------------: | :------: |
| c.accountAddress  |            0x97AF9124a95639ded09CF337D1EcB07D3B36e259            | 账户地址 |
| c.contractAddress |            0x97AF9124a95639ded09CF337D1EcB07D3B36e259            | 合约地址 |
| ethclient.Dial    |                      http://127.0.0.1:7545                       | 私链地址 |
| privateKey        | a6a1d2b6d8972d5b12b87e976822fb52f6fd8b2e6280ad69a94ea70ca16330a6 |   私钥   |

启动go-server
```shell
go run main.go 
```

访问
http://localhost:4000

### 新增和修改笔记效果
 ![exploit](src/images/add_update.gif)