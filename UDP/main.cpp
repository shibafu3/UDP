//TCP,UDP�ʐM�p���C�u����
#pragma comment(lib, "ws2_32.lib")

//TCP,UDP�ʐM�p�w�b�_
//#include <sys/sock.h> //linux
#include <WinSock2.h> //windows

#include <iostream>

// inet_addr()�֐��Ōx�����o��ꍇ�͈ȉ��Ōx���𖳌�������B
#pragma warning(disable:4996) 

// ����
// �\�P�b�g�ʐMwinsock�̗����グ
// socket�̍쐬
// �A�h���X�̐ݒ�
// socket�̐ݒ�
// ���M�E��M
// socket�̔j��
// winsock�̏I��
   
// ���l
// �����\�P�b�g�ő���M�����ł���炵��
// �\�P�b�g�ʐM�Ŏ�M������Ȃ������f�[�^�́AOS�̒ʐM�p�������ɃX�^�b�N�����炵��
   
// �Q�lURL
// http://www.geekpage.jp/programming/
// http://hensa40.cutegirl.jp/archives/780
// http://www.ne.jp/asahi/hishidama/home/tech/socket/
// http://kobold.wiki.fc2.com/wiki/%E8%A8%80%E8%AA%9E%2FC%2B%2B%2F%E3%82%B5%E3%83%B3%E3%83%97%E3%83%AB%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%A0%2FUDP%E9%80%9A%E4%BF%A1
// http://www.eonet.ne.jp/~maeda/winc/udp.htm
// http://research.nii.ac.jp/~ichiro/syspro98/
// http://keicode.com/winprimer/wp201.php

// ��M�֐�
int recieve() {
    // �\�P�b�g�ʐMwinsock�̗����グ
    // wsaData�̓G���[�擾���Ɏg�p����
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);   //MAKEWORD(2, 0)��winsock�̃o�[�W����2.0���Ă���

    // socket�쐬
    // socket�͒ʐM�̏o����� ������ʂ��ăf�[�^�̂���������
    // socket(�A�h���X�t�@�~��, �\�P�b�g�^�C�v, �v���g�R��)
    SOCKET sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);  //AF_INET��IPv4�ASOCK_DGRAM��UDP�ʐM�A0�́H

    // �A�h���X���i�[
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;  //IPv4
    addr.sin_port = htons(12345);   //�ʐM�|�[�g�ԍ��ݒ�
    addr.sin_addr.S_un.S_addr = INADDR_ANY; // INADDR_ANY�͂��ׂẴA�h���X����̃p�P�b�g����M����

    // �o�C���h
    // �A�h���X���̏���socket�ɓo�^����
    bind(sock, (struct sockaddr *)&addr, sizeof(addr));

    // �u���b�L���O�A�m���u���b�L���O�̐ݒ�
    //�i�C�ӁA�K�{�R�[�h�ł͂Ȃ��i�\�P�b�g�̏����ݒ�̓u���b�L���O���[�h�Ȃ��߁j
    // val = 0 : �u���b�L���O���[�h �f�[�^����M�����܂őҋ@
    // val = 1 : �m���u���b�L���O �f�[�^����M����Ȃ��Ă����̏�����
    u_long val = 1;
    ioctlsocket(sock, FIONBIO, &val);

    // �o�b�t�@ �����Ɏ�M�����f�[�^������ �T�C�Y�͎��R�Ɍ��߂��邪�Achar�z��
    char buf[2048];
    memset(buf, 0, sizeof(buf)); // �������M����Ƃ��͑O��l���c��Ȃ��悤�ɂ��̂悤�� �o�b�t�@��0�ŃN���A����̂���ʓI �������[����֐�

    // ��M
    // recv(�\�P�b�g, ���M����f�[�^, �f�[�^�̃o�C�g��, �t���O);
    // �o�C���h���Ă��Ȃ��ꍇ�� recvfrom(sock, buf, 5, 0, (struct sockaddr *)&addr, sizeof(addr)); �ł�OK�H
    recv(sock, buf, sizeof(buf), 0);

    // �o��
    printf("%s\n", buf);

    // socket�̔j��
    closesocket(sock);

    // winsock�̏I��
    WSACleanup();

    return 0;
}

//���M�֐�
int send() {
    // �\�P�b�g�ʐMwinsock�̗����グ
    // wsaData�̓G���[�擾���Ɏg�p����
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);   //MAKEWORD(2, 0)��winsock�̃o�[�W����2.0���Ă���

    // socket�쐬
    // socket�͒ʐM�̏o����� ������ʂ��ăf�[�^�̂���������
    // socket(�A�h���X�t�@�~��, �\�P�b�g�^�C�v, �v���g�R��)
    SOCKET sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);  //AF_INET��IPv4�ASOCK_DGRAM��UDP�ʐM�A0�́H

    // �A�h���X���i�[
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;  //IPv4
    addr.sin_port = htons(12345);   //�ʐM�|�[�g�ԍ��ݒ�
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // ���M�A�h���X��127.0.0.1�ɐݒ�

    // �o�b�t�@ �����ɑ��M����f�[�^������  �T�C�Y�͎��R�Ɍ��߂��邪�Achar�z��
    char buf[2048] = "HELLO";

    // ���M
    // sendto(�\�P�b�g, ���M����f�[�^, �f�[�^�̃o�C�g��, �t���O, �A�h���X���, �A�h���X���̃T�C�Y);
    // ���M����f�[�^�ɒ��ڕ����� "HELLO" �������邱�Ƃ��ł���
    // �o�C���h���Ă���ꍇ�� send(sock, buf, 5, 0); �ł�OK�H
    sendto(sock, buf, 5, 0, (struct sockaddr *)&addr, sizeof(addr));

    // socket�̔j��
    closesocket(sock);

    // winsock�̏I��
    WSACleanup();

    return 0;
}

int main() {
    send();
    recieve();

    return 0;
}