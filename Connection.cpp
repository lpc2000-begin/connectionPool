#include"public.h"
#include"Connection.h"
// ���ݿ�������Ϣ
//static string server = "127.0.0.1";
//static string user = "root";
//static string password = "123456";
//static string dbname = "chat";

//j9E6Sc9lCTelSE4a

// ��ʼ�����ݿ�����
Connection::Connection()
{
    _conn = mysql_init(nullptr);
}
// �ͷ����ݿ�������Դ
Connection::~Connection()
{
    if (_conn != nullptr)
    {
        mysql_close(_conn);
    }

}
// �������ݿ�
bool Connection::connect(string ip,unsigned short port,
        string user,string password,string dbname)
{
    MYSQL* p = mysql_real_connect(_conn, ip.c_str(), user.c_str(),
        password.c_str(), dbname.c_str(),port, nullptr, 0);

    /*if (p != nullptr)
    {
        // c��c++����Ĭ�ϵı����ַ�ʱASCII,��������ã���MySQL����������������ʾ��
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

// ���²���
bool Connection::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG("����ʧ�ܣ�"+sql);
        return false;
    }
    return true;
}

// ��ѯ����
MYSQL_RES* Connection::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG("��ѯʧ�ܣ�"+sql);
        return nullptr;
    }

    return mysql_use_result(_conn);
}

//��ȡ����
MYSQL* Connection::getConnection()
{
    return _conn;
}
