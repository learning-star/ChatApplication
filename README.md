# ChatApplication
This project is about a ChatApplication which bases on Value GameNetworkingSoekets.

## 项目功能模块
+ 日志模块
    * 基于spdlog，实现日志文件记录和控制台日志记录功能
    * 使用RAII，自动管理Log系统的生命周期
+ 数据管理
    * 定义Buffer数据缓冲区，实现读写函数
    * 定义数据流读写对象，提供数据流序列化反序列化接口
        - 支持trivial type
        - 自定义对象
        - 容器（map, vector）
    * 继承并实现数据流读写对象相关接口函数
## TODO
+ 编写服务器代码
+ 编写客户端代码
+ ...
