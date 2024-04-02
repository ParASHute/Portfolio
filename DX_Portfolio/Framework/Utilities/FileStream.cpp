#include "Framework.h"
#include "FileStream.h"

FileStream::FileStream(string path, uint flags)
    : flag(flags)
{
    int iosFlags = ios::binary;

    // ���� / �б� ���� �������� Ȯ��
    iosFlags |= flags && FILE_STREAM_WRITE 
        ? ios::out : 0;
    iosFlags |= flags && FILE_STREAM_READ
        ? ios::in : 0;

    if (flags & FILE_STREAM_WRITE)
    {
        // ��� ���� ��Ʈ�� ����
        out.open(path, iosFlags);
        // ���� ���� ��Ʈ���� ���������� �ʴٸ�
        if (out.fail())
        {
            // flush���� �ȵǸ� ��� ����
            out.flush(); // ������ �����
            out.close(); // ��Ʈ�� �ݱ�
            assert(false);
        }
    }
    // �б� �����
    else if (flags & FILE_STREAM_READ)
    {
        in.open(path, iosFlags);
        if (in.fail())
        {
            in.clear(); // ������ �����
            in.close(); // ��Ʈ�� �ݱ�
            assert(false);
        }
    }
}

FileStream::~FileStream()
{
    if (flag & FILE_STREAM_WRITE)
    {
        // ������ ���� ������ ����� �ݱ�
        out.flush();
        out.close();
    }
    else if (flag & FILE_STREAM_READ)
    {
        // �б��� ���� ������ ����� �ݱ�
        in.clear();
        in.close();
    }

}
