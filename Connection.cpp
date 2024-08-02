#include"public.h"
#include"Connection.h"
// 数据库配置信息
//static string server = "127.0.0.1";
//static string user = "root";
//static string password = "123456";
//static string dbname = "chat";

//j9E6Sc9lCTelSE4a

// 初始化数据库连接
Connection::Connection()
{
    _conn = mysql_init(nullptr);
}
// 释放数据库连接资源
Connection::~Connection()
{
    if (_conn != nullptr)
    {
        mysql_close(_conn);
    }

}
// 连接数据库
bool Connection::connect(string ip,unsigned short port,
        string user,string password,string dbname)
{
    MYSQL* p = mysql_real_connect(_conn, ip.c_str(), user.c_str(),
        password.c_str(), dbname.c_str(),port, nullptr, 0);

    /*if (p != nullptr)
    {
        // c和c++代码默认的编码字符时ASCII,如果不设置，从MySQL上拉下来的中文显示？
        mysql_query(_conn, "set names gdk");
        LOG("connect mysql success!");
    }
    else
    {
        LOG("connect mysql fail!");
        cout<< mysql_error(_conn);

    }*/
    return p != nullptr;
}

// 更新操作
bool Connection::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG("更新失败！"+sql);
        return false;
    }
    return true;
}

// 查询操作
MYSQL_RES* Connection::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG("查询失败！"+sql);
        return nullptr;
    }

    return mysql_use_result(_conn);
}

//获取连接
MYSQL* Connection::getConnection()
{
    return _conn;
}
