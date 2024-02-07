#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6031)
#pragma warning(disable : 4996)

void print_status(int com_left, int com_right, int user_left, int user_right);
int  judge_divide(int left, int right);
void finger(int open);
char select_action();
int  attack();
int  divide_finger();
int  is_end(int user_left, int user_right, int com_left, int com_right);

int main(void)
{
    int  turn = 0;
    char answer;
    char behavior_answer;
    char myhand_select_user;
    char yourhand_select_user;
    char select_action_result;
    int  c;

    int com_left           = 1;
    int com_right          = 1;
    int user_left          = 1;
    int user_right         = 1;
    int user_left_finger   = 0;
    int user_right_finger  = 0;
    int hand_select_result = 0;
    int dividefinger       = 0;

    while (1) 
    {
        while (1) 
        {
            com_left   = 1;
            com_right  = 1;
            user_left  = 1;
            user_right = 1;

            printf("���ο� ������ �����ұ��? [Y or N]\n");
            scanf("%c", &answer);
            while (c = fgetc(stdin) != '\n' && c != EOF);
            if (answer == 'Y') 
            {
                printf("������ ���۵Ǿ����ϴ�.\n");
                break;
            }
            else if (answer == 'N') 
            {
                printf("������ �����մϴ�.\n");
                exit(0);
            }
            else 
            {
                printf("�ùٸ��� ���� ��ɾ��Դϴ�.\n\n");
            }
        }

        print_status(com_left, com_right, user_left, user_right);
        srand(time(NULL));
        turn = rand() % 2;

        while (1) 
        {
            if (turn == 0) 
            {
                printf("\n\nUSER �����Դϴ�.\n");
                while (1)
                {
                    printf("� �ൿ�� �Ͻðڽ��ϱ�? [A: ���� D: ������]\n");
                    scanf("%c", &behavior_answer); while (c = fgetc(stdin) != '\n' && c != EOF);
                    if (behavior_answer == 'D') 
                    {
                        if (judge_divide(user_left, user_right) == 1) 
                        {
                            break;
                        }
                        else 
                        {
                            printf("�Ұ����� �ൿ�Դϴ�.\n");
                        }
                    }
                    else 
                    {
                        break;
                    }
                }
                if (behavior_answer == 'A') 
                {
                    while (1) 
                    {
                        printf("��� ������ �����Ͻðڽ��ϱ�? [L: �޼� R: ������]\n");
                        scanf("%c", &myhand_select_user); while (c = fgetc(stdin) != '\n' && c != EOF);
                        if (myhand_select_user == 'L') 
                        {
                            if (user_left == 0) 
                            {
                                printf("������ �� �����ϴ�.\n\n");
                            }
                            else 
                            {
                                break;
                            }
                        }
                        else if (myhand_select_user == 'R') 
                        {
                            if (user_right == 0) 
                            {
                                printf("������ �� �����ϴ�.\n\n");
                            }
                            else 
                            {
                                break;
                            }
                        }
                        else 
                        {
                            printf("�ùٸ��� ���� ��ɾ��Դϴ�.\n\n");
                        }
                    }
                    
                    while (1) 
                    {
                        printf("������ ��� ���� �����Ͻðڽ��ϱ�? [L: �޼� R: ������]\n");
                        scanf("%c", &yourhand_select_user); while (c = fgetc(stdin) != '\n' && c != EOF);
                        if (yourhand_select_user == 'R') 
                        {
                            if (myhand_select_user == 'L') 
                            {
                                com_right += user_left;
                                if (com_right >= 5)
                                {
                                    com_right = 0;
                                }
                                break;
                            }
                            else if (myhand_select_user == 'R') 
                            {
                                com_right += user_right;
                                if (com_right >= 5)
                                {
                                    com_right = 0;
                                }
                                break;
                            }
                        }
                        else if (yourhand_select_user == 'L') 
                        {
                            if (myhand_select_user == 'L') 
                            {
                                com_left += user_left;
                                if (com_left >= 5)
                                {
                                    com_left = 0;
                                }
                                break;
                            }
                            else if (myhand_select_user == 'R')
                            {
                                com_left += user_right;
                                if (com_left >= 5)
                                {
                                    com_left = 0;
                                }
                                break;
                            }
                        }
                        else 
                        {
                            printf("�ùٸ��� ���� ��ɾ��Դϴ�.\n\n\n");
                        }
                    }
                }
                else if (behavior_answer == 'D') 
                {
                    while (1) 
                    {
                        printf("��� �����ðڽ��ϱ�? (0�̻�~4������ ������ �Է����ּ���.)\n");

                        while (1) 
                        {
                            printf("�޼� �հ���:\n");
                            scanf("%d", &user_left_finger);
                            if (user_left_finger >= 0 && user_left_finger <= 4) 
                            {
                                break;
                            }
                            else 
                            {
                                printf("�ùٸ� ���� �Է����ּ���.\n");
                            }
                        }

                        while (1) 
                        {
                            printf("������ �հ���:\n");
                            scanf("%d", &user_right_finger);
                            if (user_right_finger >= 0 && user_right_finger <= 4) 
                            {
                                break;
                            }
                            else 
                            {
                                printf("�ùٸ� ���� �Է����ּ���.\n");
                            }
                        }

                        //�Ʒ� ���� �����ʿ� �ҽ��� ���� ����� �ٷ� ���� �� �� �ֶǷ�  �ش��ϴ� �ּ��� �� �� ��.
                        if (   (user_left_finger + user_right_finger) != (user_left + user_right)    //
                            || (user_left_finger == user_right && user_right_finger == user_left)    //
                            || (user_left_finger == user_left  && user_right_finger == user_right))  //
                        {
                            printf("�Ұ����� �������Դϴ�.\n\n");
                            continue;
                        }

                        user_left  = user_left_finger;
                        user_right = user_right_finger;

                        break;
                    }
                }

                if (user_left >= 5)
                {
                    user_left = 0;
                }
                else if (user_right >= 5)
                {
                    user_right = 0;
                }
                else if (com_left >= 5)
                {
                    com_left = 0;
                }
                else if (com_right >= 5)
                {
                    com_right = 0;
                }

                print_status(com_left, com_right, user_left, user_right);

                if (is_end(user_left, user_right, com_left, com_right) == 1)
                {
                    if (user_left == 0 && user_right == 0)
                    {
                        printf("COMPUTER�� �¸��Դϴ�.\n\n\n");  //USER�� ���ʿ����� COMPUTER�� �¸��� ���� �� ���� ��.
                        break;
                    }
                    else
                    {
                        printf("USER�� �¸��Դϴ�.\n\n\n");
                        break;
                    }
                }
                turn = 1;
            }
            else 
            {
                printf("\n\nCOMPUTER �����Դϴ�.\n");
                while (1)
                {
                    select_action_result = select_action();
                    if (select_action_result == 'd') 
                    {
                        if (judge_divide(com_left, com_right) == 1) 
                        {
                            break;
                        }
                        else 
                        {
                            continue;
                        }
                    }
                    else 
                    {
                        break;
                    }
                }

                if (select_action_result == 'a') 
                {
                    while (1) 
                    {
                        hand_select_result = attack();
                        if (hand_select_result == 0) 
                        {
                            if (com_left == 0 || user_left == 0) 
                            {
                                continue;
                            }
                            else 
                            {
                                printf("COMPUTER�� [�޼�����] USER�� [�޼�]�� <����>�Ͽ����ϴ�.\n\n");
                                user_left += com_left;
                                break;
                            }
                        }
                        else if (hand_select_result == 1) 
                        {
                            if (com_right == 0 || user_left == 0) 
                            {
                                continue;
                            }
                            else {
                                printf("COMPUTER�� [����������] USER�� [�޼�]�� <����>�Ͽ����ϴ�.\n\n");
                                user_left += com_right;
                                break;
                            }
                        }
                        else if (hand_select_result == 2) 
                        {
                            if (com_left == 0 || user_right == 0) 
                            {
                                continue;
                            }
                            else 
                            {
                                printf("COMPUTER�� [�޼�����] USER�� [������]�� <����>�Ͽ����ϴ�.\n\n");
                                user_right += com_left;
                                break;
                            }
                        }
                        else 
                        {
                            if (com_right == 0 || user_right == 0) 
                            {
                                continue;
                            }
                            else 
                            {
                                printf("COMPUTER�� [����������] USER�� [������]�� <����>�Ͽ����ϴ�.\n\n");
                                user_right += com_right;
                                break;
                            }
                        }
                    }

                    if (user_left >= 5)
                    {
                        user_left = 0;
                    }
                    else if (user_right >= 5)
                    {
                        user_right = 0;
                    }
                    else if (com_left >= 5)
                    {
                        com_left = 0;
                    }
                    else if (com_right >= 5)
                    {
                        com_right = 0;
                    }
                }
                else 
                {    
                    printf("COMPUTER�� <������> �ൿ�� �Ͽ����ϴ�.\n\n");
                    while (1) 
                    {
                        dividefinger = divide_finger();
                        if (dividefinger == 0)
                        {
                            //�Ʒ��� ������ ����, � ��쿡�� Continue �̹Ƿ� ���ǹ��� �ʿ� ����. �׳� �Ʒ� Logic �� ����� continue�� �ϸ� ��.
                            //continue�� �ʿ� ����. �ڵ����� while�� ó������ ���� ������
                            if (com_left + com_right == 1)
                            {
                                continue;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        else if (dividefinger == 1)
                        {
                            if (com_left + com_right == 2)
                            {
                                if (com_left != 2 && com_right != 0 && com_left != 0 && com_right != 2)
                                {
                                    com_left  = 0;
                                    com_right = 2;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 2)
                        {
                            if (com_left + com_right == 3)
                            {
                                if (com_left != 3 && com_right != 0 && com_left != 0 && com_right != 3)
                                {
                                    com_left  = 0;
                                    com_right = 3;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 3)
                        {
                            if ((com_left + com_right) == 4)  //()�� ������.
                            {
                                if (com_left != 4 && com_right != 0 && com_left != 0 && com_right != 4)
                                {
                                    com_left  = 0;
                                    com_right = 4;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 4)
                        {
                            //�Ʒ��� ������ ����, � ��쿡�� Continue �̹Ƿ� ���ǹ��� �ʿ� ����. �׳� �Ʒ� Logic �� ����� continue�� �ϸ� ��.
                            //continue�� �ʿ� ����. �ڵ����� while�� ó������ ���� ������
                            if ((com_left + com_right) == 1)  //()�� ������.
                            {
                                continue;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        else if (dividefinger == 5)
                        {
                            if ((com_left + com_right) == 2)  //()�� ������.
                            {
                                if (com_left != 0 && com_right != 2 && com_left != 2 && com_right != 0)
                                {
                                    com_left  = 2;
                                    com_right = 0;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 6)
                        {
                            if ((com_left + com_right) == 3)  //()�� ������.
                            {
                                if (com_left != 0 && com_right != 3 && com_left != 3 && com_right != 0)
                                {
                                    com_left  = 3;
                                    com_right = 0;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 7)
                        {
                            if ((com_left + com_right) == 4)  //()�� ������.
                            {
                                if (com_left != 0 && com_right != 4 && com_left != 4 && com_right != 0)
                                {
                                    com_left  = 4;
                                    com_right = 0;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 8)
                        {
                            if ((com_left + com_right) == 2)  //()�� ������.
                            {
                                if (com_left != 1 && com_right != 1)
                                {
                                    com_left  = 1;
                                    com_right = 1;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 9)
                        {
                            if ((com_left + com_right) == 3)  //()�� ������.
                            {
                                if (com_left != 1 && com_right != 2 && com_left != 2 && com_right != 1)
                                {
                                    com_left  = 2;
                                    com_right = 1;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 10)
                        {
                            if ((com_left + com_right) == 4)  //()�� ������.
                            {
                                if (com_left != 1 && com_right != 3 && com_left != 3 && com_right != 1)
                                {
                                    com_left  = 3;
                                    com_right = 1;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 11)
                        {
                            if ((com_left + com_right) == 5)  //()�� ������.
                            {
                                if (com_left != 1 && com_right != 4 && com_left != 4 && com_right != 1)
                                {
                                    com_left  = 4;
                                    com_right = 1;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 12)
                        {
                            if ((com_left + com_right) == 3)  //()�� ������.
                            {
                                if (com_left != 2 && com_right != 1 && com_left != 1 && com_right != 2)
                                {
                                    com_left  = 1;
                                    com_right = 2;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 13)
                        {
                            if ((com_left + com_right) == 4)  //()�� ������.
                            {
                                if (com_left != 2 && com_right != 2)
                                {
                                    com_left  = 2;
                                    com_right = 2;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 14)
                        {
                            if ((com_left + com_right) == 5)  //()�� ������.
                            {
                                if (com_left != 2 && com_right != 3 && com_left != 3 && com_right != 2)
                                {
                                    com_left  = 3;
                                    com_right = 2;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 15)
                        {
                            if ((com_left + com_right) == 6)  //()�� ������.
                            {
                                if (com_left != 2 && com_right != 4 && com_left != 4 && com_right != 2)
                                {
                                    com_left  = 4;
                                    com_right = 2;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 16)
                        {
                            if ((com_left + com_right) == 4)  //()�� ������.
                            {
                                if (com_left != 3 && com_right != 1 && com_left != 1 && com_right != 3)
                                {
                                    com_left  = 1;
                                    com_right = 3;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 17)
                        {
                            if ((com_left + com_right) == 5)  //()�� ������.
                            {
                                if (com_left != 3 && com_right != 2 && com_left != 2 && com_right != 3)
                                {
                                    com_left = 2;
                                    com_right = 3;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 18)
                        {
                            if ((com_left + com_right) == 6)  //()�� ������.
                            {
                                if (com_left != 3 && com_right != 3)
                                {
                                    com_left = 3;
                                    com_right = 3;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 19)  //if �տ� else�� ������ �߰���.
                        {
                            //�Ʒ��� ������ ����, � ��쿡�� Continue �̹Ƿ� ���ǹ��� �ʿ� ����. �׳� �Ʒ� Logic �� ����� continue�� �ϸ� ��.
                            //continue�� �ʿ� ����. �ڵ����� while�� ó������ ���� ������
                            if (com_left + com_right == 7)
                            {
                                continue;
                            }
                            else
                            {
                                continue;
                            }
                        }
                        else if (dividefinger == 20)
                        {
                            if (com_left + com_right == 5)
                            {
                                if (com_left != 4 && com_right != 1 && com_left != 1 && com_right != 4)  //�ּ� �� ��.
                                {
                                    com_left = 1;
                                    com_right = 4;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 21)
                        {
                            if (com_left + com_right == 6)
                            {
                                if (com_left != 4 && com_right != 2 && com_left != 2 && com_right != 4)  //�ּ� �� ��.
                                {
                                    com_left = 2;
                                    com_right = 4;
                                    break;
                                }
                            }
                        }
                        else  //���ʿ��� �ڵ�. else ���� �� �ʿ����. �ڵ����� while�� ó������ ���� ������.
                        {
                            continue;
                        }
                    }
                }

                print_status(com_left, com_right, user_left, user_right);

                if (is_end(user_left, user_right, com_left, com_right) == 1)
                {
                    if (user_left == 0 && user_right == 0)
                    {
                        printf("COMPUTER�� �¸��Դϴ�.\n\n\n");
                        break;
                    }
                    else
                    {
                        printf("USER�� �¸��Դϴ�.\n\n\n");  //COMPUTER�� ���ʿ����� USER�� �¸��� ���� �� ���� ��.
                        break;
                    }
                }
                turn = 0;
            }
        }
    }
}

void print_status(int com_left, int com_right, int user_left, int user_right)
{
    printf("\n===========================================================\n");
    printf("[COMPUTER�� �հ���] �޼�: ");
    finger(com_left);
    printf(" ������: ");
    finger(com_right);
    printf("\n");
    printf("[USER�� �հ���]     �޼�: ");
    finger(user_left);
    printf(" ������: ");
    finger(user_right);
    printf("\n===========================================================\n");
}

int judge_divide(int left, int right) 
{
    //�����ʿ� �ּ� �� ��.
    if (left == 0 && right == 1)       //
    {
        return 0;
    }
    else if (left == 1 && right == 0)  //
    {
        return 0;
    }
    else if (left == 3 && right == 4)  //
    {
        return 0;
    }
    else if (left == 4 && right == 3)  //
    {
        return 0;
    }
    else if (left == 4 && right == 4)  //
    {
        return 0;
    }

    return 1;
}

void finger(int open)
{
    for (int i = 1; i <= 5; i++)
    {
        if (i <= open)
        {
            printf("��");
        }
        else
        {
            printf("��");
        }
    }
}

char select_action() 
{
    int choice_behavior = 0;

    srand(time(NULL));

    choice_behavior = rand() % 2;
    if (choice_behavior == 0)
    {
        return 'a';
    }
    else
    {
        return 'd';
    }
}

int attack() 
{
    //�޼��� 0, �������� 1�� ���� <== ���� ���� �ּ��� ����. ���� ���!!!
    int attack = 4;
    //�Ʒ����� ���� �������Ƿ� ������ �ʱⰪ �� �ʿ� ����, ���� ���ʿ��ϰ� ���� ������ ���� �ʾƵ� ��.
    //������ ���� �ϸ� �� => return rand() % 24

    srand(time(NULL));

    attack = rand() % 4;

    return attack;
}

int divide_finger()
{
    int dividefinger = 50;
    //�������� �ܾ�� �ܾ� ���̸� underscore('_')�� ������ �ִ°� ����. => divide_finger.
    //�Ʒ����� ���� �������Ƿ� ������ �ʱⰪ �� �ʿ� ����, ���� ���ʿ��ϰ� ���� ������ ���� �ʾƵ� ��.
    //������ ���� �ϸ� �� => return rand() % 24

    srand(time(NULL));

    dividefinger = rand() % 24;

    return dividefinger;
}

int is_end(int user_left, int user_right, int com_left, int com_right) 
{
    if (user_left == 0 && user_right == 0)
    {
        return 1;
    }
    else if (com_left == 0 && com_right == 0)
    {
        return 1;
    }

    return 0;
}




/*
void print_status() : ����â�� ����մϴ�.

int is_end() : �� ������ ������ ����Ǿ��� �� �˻��ϴ� �Լ��Դϴ�. ���� ��� ������ ����Ǿ��ٸ� 1, �׷��� �ʴٸ� 0 �� ��ȯ�մϴ�.

char select_action() : COMPUTER �� ���ʿ��� �ൿ (����/������)�� �����ϴ� �Լ��Դϴ�.

int attack() : COMPUTER �� ������ �����Ͽ��� �� �ڽ��� � ������ USER �� � ���� �������� �����ϴ� �Լ��Դϴ�. ���� ��� ���� ��
������ ������ 4 �����̱⿡ �̴� ������ ��ȯ�� 0~3 �� ���� ������
�� �ֽ��ϴ�. ��, ������ ������ ��Ģ�� �����ϴ� �ൿ�� �� �� ��
��� �մϴ�.

int divide_finger() : COMPUTER �� �����⸦ �����Ͽ��� �� ��� ���� �� �����ϴ�
�Լ��Դϴ�. ���� ��� ������ �� ������ ������ 25 �����̱⿡ ��
�� ������ ��ȯ�� 0~24 �� ���� ������ �� �ֽ��ϴ�. ��, ������
������ ��Ģ�� �����ϴ� �ൿ�� �� �� ����� �մϴ�.
*/

