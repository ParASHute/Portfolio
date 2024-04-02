#include "Framework.h"
#include "Random.h"

int Random::GetRandomInt(int minValue, int maxValue)
{
    /*
    random_device�� ���α׷��Ӱ� ���� �Ҽ����� �������� ������ 
    ������ ������� �ڵ����� �Ҹ�ȴ�.

    ����, random_device�� ȣ���� �� ���� �ٸ� �������� ����Ѵ�.
    */
    random_device randDevice; // ��Ű srand

    /*
    uniform_int_distribution�� �̾Ƴ� �������� �ڷ����� ������ �����Ҽ� �ִ�.
    
    ����� <>�� �Է��� <>��ÿ� ��������� ���ϴ� �ڷ����� �Է��Ҽ� �ְ�

    uniform_int_distribution�� ������ ����� ������� ���� �� �ִ�.

    uniform_int<> ���� �Ȱ��� �۵��� ������ ����� �ȳ��� ���� ���� ���� ������
    uniform_int_distribution�� ����

    ������ ���ϴ� �������� ������ ()�� ����ϰ� ���� �ּ� ���� �ִ밪�� �־��ָ�
    �ȴ�.

    �̶� �ּҰ��� �ִ밪�� �����ϴ� ������ ���� ����Ѵ�.
    Ex) intRand(100,200) �̸� 100 ~ 200 ������ ���ڰ� ���´�.
    */
    uniform_int_distribution<int> intRand(minValue, maxValue);

    /*
    ���� ���� ����� ���� ���ؼ��� uniform�� rand_device�� �����Ͽ� ��µ�
    �����͸� ������ �־���� �Ѵ�.

    �̶� ������ �־��ֱ� �������� ������ �����ͷν� �ν��� ���� �ʱ� ������
    �ش� �����͸� ���̷�Ʈ�� �����ϰų� �����Ҷ� ������ �߻��� ���� �ִ�.

    �߰��� intRand(randDevice)�� �Ȱ��� ������ �����͸� ������ ȣ���� ������
    ����־ �Ź� �ٸ� ������� �����Ͱ� ����.
    */
    int aValue = intRand(randDevice);

    return aValue;
}

float Random::GetRandomFloat(float minValue, float maxValue)
{
    random_device randDevice;

    /*
    �Ǽ����� �������� ��� ���ؼ��� uniform_real ������ Ŭ������ ����ϸ� �ȴ�.

    �̶� ���ǻ����� �Ǽ����� ������ �Ϲ����� �������� �޸� ǥ���Ҽ� �ִ� �ڸ�����
    ��簪�� ������ ������ ���� ������ �������� ��� �ſ� ��ư�

    �ſ� ���������� �����ؾ� �ϱ� ������ ��õ���� �ʴ´�.

    Ex) floatRand(0.5f, 1.0f)
    0.5000000 ~ 1.0000000 ������ �����̱� ������
    ��� ������ 0.7842516 ���� ���� ���ü��� �ִ�.
    */
    uniform_real_distribution<float> floatRand(minValue, maxValue);

    float aValue = floatRand(randDevice);

    return aValue;
}
