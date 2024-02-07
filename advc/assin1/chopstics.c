#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TURN_COM      0
#define TURN_USER     1

#define SEL_ATTACK    0
#define SEL_DIVIDE    1

#define FINGER_CNT    5

#define MIN_FINGER    0
#define MAX_FINGER    4

int  get_rand_number(unsigned int, unsigned int);
int  choice_num(char *, int, int);
char choice_char(char *, char, char);
void print_status(int, int, int, int);
int  check_divde_rule(int, int);
int  is_end(int, int);
char select_action();
int  attack();
int  divide_finger();

//�հ����� ����ϴ� ����� ��������(�ݺ������� ���, printf formatting���� ��� ��)�� ������
//�迭�� ������ �ΰ�, ���� �����ϴ� ����� ���� ȿ�����̶� �Ǵ��Ͽ� "char *" �迭�� �����.
//�迭�� �ε����� 0���� �����ϹǷ�, �հ��� ������ �����ϰ� ���߱� ���ؼ�
//ù��°�� ��� �հ����� �������·� �����ϰ�, �ι�° ������ ��ģ �հ����� ������.
//����, �迭����� �� ������ 6��(�հ����� 5�� + NULL)��.
static char *open_finger[6] = {
    "������",  //0
    "������",  //1
    "������",  //2
    "������",  //3
    "������",  //4
    "������"   //5
};

int
main(void)
{
    int  ret = 0;
    bool turn;
    int  com_l_finger = 1, com_r_finger = 1, user_l_finger = 1, user_r_finger = 1;
    int  sel_div_finger;
    char is_div_ok = 'Y';
    char input;
    char sel_atk_div;
    char sel_atk_hand;
    char sel_atk_user_hand;
    char sel_com_hand;
    char sel_result;

    while (1)
    {
        while (1)
        {
            input = choice_char("���ο� ������ �����ұ��? [Y or N]\n", 'Y', 'N');
            if (input == 'Y')
            {
                printf("\n������ ���۵Ǿ����ϴ�.\n");
                break;
            }
            else if (input == 'N')
            {
                printf("\n������ �����մϴ�.\n");
                exit(0);
            }
            else
            {
                printf("\n�ùٸ��� ���� ��ɾ��Դϴ�.\n\n");
            }
        }  //End of while

        //������ ������ �����ϰ� ��ǻ�� �޼�/������, USER �޼�/������ ������ ���ڸ� ������.
        print_status(com_l_finger, com_r_finger, user_l_finger, user_r_finger);

        //���� �����ڸ� �������� ������.
        turn = get_random_number(0, 1);
        printf("turn=[%d]-[%s]\n", turn, turn == TURN_COM ? "COMPUTER" : "USER");

        while (1)
        {
            if (turn == TURN_USER)  //USER ����
            {
                sel_atk_div = choice_char("USER �����Դϴ�.\n� �ൿ�� �Ͻðڽ��ϱ�? [A:���� D:������]\n", 'A', 'D');

                if (sel_atk_div == 'A')  //����
                {
                    sel_atk_user_hand = choice_char("��� ������ �����Ͻðڽ��ϱ�? [L:�޼� R:������]\n", 'L', 'R');
                    printf("sel_atk_user_hand=[%c]\n", sel_atk_user_hand);

                    sel_com_hand = choice_char("������ ��� ���� �����Ͻðڽ��ϱ�? [L:�޼� R:������]\n", 'L', 'R');
                    printf("sel_com_hand=[%c]\n", sel_com_hand);

                    if (sel_com_hand == 'L')  //COMPUTER�� �޼��� �����ϴ� ���
                    {
                        if (sel_atk_user_hand == 'L')  //USER�� ���� �޼��� ���.
                        {
                            com_l_finger += user_l_finger;  //COMPUTER�� �޼տ� USER�� �޼� ��ģ �հ��� ������ ���Ѵ�.
                        }
                        else  //'R'-USER�� ���� �������� ���
                        {
                            com_l_finger += user_r_finger;  //COMPUTER�� �޼տ� USER�� ������ ��ģ �հ��� ������ ���Ѵ�.
                        }
                    }
                    else  //sel_com_hand == 'R'. COMPUTER�� �������� �����ϴ� ���. choice_char �Լ������� 'L', 'R'�� ��ȯ�� �����ϹǷ� else�� ������ 'R'�̶�� ���� ��.
                    {
                        if (sel_atk_user_hand == 'L')  //�޼�
                        {
                            com_r_finger += user_l_finger;  //COMPUTER�� �����տ� USER�� �޼� ��ģ �հ��� ������ ���Ѵ�.
                        }
                        else  //'R'-������
                        {
                            com_r_finger += user_r_finger;  //COMPUTER�� �����տ� USER�� ������ ��ģ �հ��� ������ ���Ѵ�.
                        }
                    }

                    ret = is_end(com_l_finger, com_r_finger);
                    if (ret == 0)  //COMPUTER�� �޼�, �������� �հ����� ��� ������ ���.
                    {
                        printf("USER�� �¸��Դϴ�.\n");
                        break;  //���α׷��� �� ó������ ���ư�.
                    }
                }
                else if (sel_atk_div == 'D')  //������
                {
                    while (1)
                    {
                        printf("��� �����ðڽ��ϱ�? (0�̻�~4������ ������ �Է����ּ���.)\n");
                        input_l_finger = choice_num("�޼� �հ���:\n",   MIN_FINGER, MAX_FINGER);
                        input_r_finger = choice_num("������ �հ���:\n", MIN_FINGER, MAX_FINGER);

                        ret = check_divide_rule();
                        if (ret != 0)
                        {
                            printf("�Ұ����� ������ �Դϴ�.\n");
                            continue;
                        }

                        if ((input_l_finger+input_r_finger) == (user_l_finger+user_r_finger))
                        {
                            user_l_finger = input_l_finger;
                            user_r_finger = input_r_finger;
                            break;
                        }
                    }  //End of while

                    if (is_div_ok == 'N')
                    {
                        //USER ���� ó������ �ٽ� �ǵ��� ��.
                        continue;
                    }

                    //���ʸ� �ٲ�. => turn�� �ٲ��� �ʾƵ� �ڿ������� �귯�� turn�� �ٲ�.
                    //turn = !turn;  //NOT(!) �����ڸ� ����ϸ� 1(USER)�� 0(COMPUTER)�� toggle ��.
                    //continue;  //���� continue�� ���� �ʾƵ� �Ʒ����� turn�� �ٲ�� while���� ó������ ���ư�.
                }
            }
            else  //��ǻ�� ����(TURN_COM)
            {
                printf("COMPUTER �����Դϴ�.\n");

                sel_atk_div = select_action();
                sel_result  = attack();

                //0: �޼�����   USER�� �޼�   ����
                //1: �޼�����   USER�� ������ ����
                //2: ���������� USER�� �޼�   ����
                //3: ���������� USER�� ������ ����
                if (sel_atk_div == 'A')  //����
                {
                    if (sel_result == '0')              //COMPUTER�� �޼����� USER�� �޼��� �����ϴ� ���
                    {
                        user_l_finger += com_l_finger;  //USER�� �޼տ� COMPUTER�� �޼� ��ģ �հ��� ������ ���Ѵ�.
                    }
                    else if (sel_result == '1')         //COMPUTER�� �޼����� USER�� �������� �����ϴ� ���
                    {
                        user_r_finger += com_l_finger;  //USER�� �޼տ� COMPUTER�� ������ ��ģ �հ��� ������ ���Ѵ�.
                    }
                    else if (sel_result == '2')         //COMPUTER�� ���������� USER�� �޼��� �����ϴ� ���
                    {
                        user_l_finger += com_r_finger;  //USER�� �����տ� USER�� ������ ��ģ �հ��� ������ ���Ѵ�.
                    }
                    else if (sel_result == '3')         //COMPUTER�� ���������� USER�� �������� �����ϴ� ���
                    {
                        user_r_finger += com_r_finger;  //USER�� �޼տ� COMPUTER�� ������ ��ģ �հ��� ������ ���Ѵ�.
                    }

                    ret = is_end(user_l_finger, user_r_finger);
                    if (ret == 0)  //COMPUTER�� �޼�, �������� �հ����� ��� ������ ���.
                    {
                        printf("COMPUTER�� �¸��Դϴ�.\n");
                        break;  //���α׷��� �� ó������ ���ư�.
                    }
                }
                else if (sel_atk_div == 'D')  //������
                {
                    sel_result = divide_finger();

                    //���ʸ� �ٲ�.
                    turn = !turn;  //NOT(!) �����ڸ� ����ϸ� 1(USER)�� 0(COMPUTER)�� toggle ��.
                    continue;
                }
            }
        
            //���ʸ� �ٲ�.
            turn = !turn;  //0�� 1�� toggle ó��(NOT���� ����)
        }  //End of while
    }  //End of while

    return 0;
}

int
get_random_number(unsigned int range_min, unsigned int range_max)
{
    range = 0;

    if (range_min >= range_max)
    {
        printf("���������� �ּҰ��� �ִ밪���� �۾ƾ� �մϴ�.\n");
        return -1;
    }

    range = range_max - range_min + 1;

    srand((unsigned int)time(NULL));

    return rand() % range;
}

//���ڸ� �Է¹޾� ��ȯ�ϴ� �Լ�.
// - question : ���� String. ���� �߸� �Է�������, �������� ���� �ݺ��ϵ��� ���ڷ� ����.
// - min_num  : �ּҰ�
// - max_num  : �ִ밪
int
choice_num(char *question, int min_num, int max_num)
{
    int  c, number;

    while (1)
    {
        printf(question);
        scanf("%d", &number);
        while(c = fgetc(stdin) != '\n' && c != EOF);  //Carriage Return ���� �Ǵ� EOF�� �ƴϸ� ��� flush ó��.

        if (number >= min_num && number <= max_num)  //���� ���� ���ڸ� �Է¹޵��� ó��.
        {
            break;
        }

        printf("�ùٸ� ���� �Է��� �ּ���.\n");
    }

    return number;
}

//���ڸ� �Է¹޾� ��ȯ�ϴ� �Լ�.
// - question : ���� String. ���� �߸� �Է�������, �������� ���� �ݺ��ϵ��� ���ڷ� ����.
// - sel1 : �ʼ��Է¹���1
// - sel2 : �ʼ��Է¹���2
char
choice_char(char *question, char sel1, char sel2)
{
    int  c;
    char character;

    while (1)
    {
        printf(question);
        scanf("%c", &character);
        while(c = fgetc(stdin) != '\n' && c != EOF);  //Carriage Return ���� �Ǵ� EOF�� �ƴϸ� ��� flush ó��.

        if (character == sel1 || character == sel2)  //������ ���� �Էµ��� ������, �ٽ� �Է� �޵��� ó��.
        {
            break;
        }
        else
        {
            printf("�ùٸ� ���� �Է��� �ּ���.\n");
        }
    }

    return character;
}

//����â�� ����մϴ�.
void
print_status(int u_left, int u_right, int c_left, int c_right)
{
  printf("===========================================================\n");
  printf("[COMPUTER�� �հ���] �޼�: %s ������: %s\n", open_finger[c_left], open_finger[c_right]);
  printf("[USER�� �հ���]     �޼�: %s ������: %s\n", open_finger[u_left], open_finger[u_right]);
  printf("===========================================================\n");
}

int
check_divde_rule(int left_finger, int right_finger)
{
    return 0;
}

int
is_end(int left_finger_cnt, int right_finger_cnt)
{
    if (left_finger_cnt >= FINGER_CNT && right_finger_cnt >= FINGER_CNT)  //�޼�, �������� �հ����� ��� ������ ���.
    {
        return 0;
    }

    return -1;
}

//COMPUTER �� ���ʿ��� �ൿ (����/������)�� �����ϴ� �Լ��Դϴ�.
char
select_action()
{
    int  ret = 0;
    char sel_atk_div;

    //COMPUTER �����Դϴ�. � �ൿ�� �Ͻðڽ��ϱ�? [A:���� D:������]
    //����/������ Random ó��.
    ret = get_random_number(0, 1);  //�ΰ��� ���
    if (ret == 0)
    {
        sel_atk_div = 'A';
    }
    else if (ret == 1)
    {
        sel_atk_div = 'D';
    }
    else
    {
        printf("get_random_number ȣ�� �����Դϴ�. ���α׷� Ȯ���� �ʿ��մϴ�. ret=[%d]\n", ret);
        exit(-1);
    }
    
    printf("sel_atk_div = [%c]\n", sel_atk_div);

    return sel_atk_div;
}

//COMPUTER �� ������ �����Ͽ��� �� �ڽ��� � ������ USER ��
//� ���� �������� �����ϴ� �Լ��Դϴ�. ���� ��� ���� �� ����
//�� ������ 4 �����̱⿡ �̴� ������ ��ȯ�� 0~3 �� ���� ������
//�� �ֽ��ϴ�. ��, ������ ������ ��Ģ�� �����ϴ� �ൿ�� �� �� ��
//��� �մϴ�.
int
attack()
{
    int ret = 0;

    //0: �޼�����   USER�� �޼�   ����
    //1: �޼�����   USER�� ������ ����
    //2: ���������� USER�� �޼�   ����
    //3: ���������� USER�� ������ ����
    ret = get_random_number(0, 3);
    if (ret < 0 || ret > 3)
    {
        printf("������� ��ȿ���� �ʽ��ϴ�. ret=[%d]\n", ret);
        exit(-1);
    }

    return 0;
}

//COMPUTER �� �����⸦ �����Ͽ��� �� ��� ���� �� �����ϴ�
//�Լ��Դϴ�. ���� ��� ������ �� ������ ������ 25 �����̱⿡ ��
//�� ������ ��ȯ�� 0~24 �� ���� ������ �� �ֽ��ϴ�. ��, ������
//������ ��Ģ�� �����ϴ� �ൿ�� �� �� ����� �մϴ�.
int
divide_finger()
{
    int ret = 0;

    ret = get_random_number(0, 24);

    return 0;
}
