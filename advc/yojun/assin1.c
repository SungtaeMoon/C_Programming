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

            printf("새로운 게임을 시작할까요? [Y or N]\n");
            scanf("%c", &answer);
            while (c = fgetc(stdin) != '\n' && c != EOF);
            if (answer == 'Y') 
            {
                printf("게임이 시작되었습니다.\n");
                break;
            }
            else if (answer == 'N') 
            {
                printf("게임을 종료합니다.\n");
                exit(0);
            }
            else 
            {
                printf("올바르지 않은 명령어입니다.\n\n");
            }
        }

        print_status(com_left, com_right, user_left, user_right);
        srand(time(NULL));
        turn = rand() % 2;

        while (1) 
        {
            if (turn == 0) 
            {
                printf("\n\nUSER 차례입니다.\n");
                while (1)
                {
                    printf("어떤 행동을 하시겠습니까? [A: 공격 D: 나누기]\n");
                    scanf("%c", &behavior_answer); while (c = fgetc(stdin) != '\n' && c != EOF);
                    if (behavior_answer == 'D') 
                    {
                        if (judge_divide(user_left, user_right) == 1) 
                        {
                            break;
                        }
                        else 
                        {
                            printf("불가능한 행동입니다.\n");
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
                        printf("어느 손으로 공격하시겠습니까? [L: 왼손 R: 오른손]\n");
                        scanf("%c", &myhand_select_user); while (c = fgetc(stdin) != '\n' && c != EOF);
                        if (myhand_select_user == 'L') 
                        {
                            if (user_left == 0) 
                            {
                                printf("공격할 수 없습니다.\n\n");
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
                                printf("공격할 수 없습니다.\n\n");
                            }
                            else 
                            {
                                break;
                            }
                        }
                        else 
                        {
                            printf("올바르지 않은 명령어입니다.\n\n");
                        }
                    }
                    
                    while (1) 
                    {
                        printf("상대방의 어느 손을 공격하시겠습니까? [L: 왼손 R: 오른손]\n");
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
                            printf("올바르지 않은 명령어입니다.\n\n\n");
                        }
                    }
                }
                else if (behavior_answer == 'D') 
                {
                    while (1) 
                    {
                        printf("어떻게 나누시겠습니까? (0이상~4이하의 정수를 입력해주세요.)\n");

                        while (1) 
                        {
                            printf("왼손 손가락:\n");
                            scanf("%d", &user_left_finger);
                            if (user_left_finger >= 0 && user_left_finger <= 4) 
                            {
                                break;
                            }
                            else 
                            {
                                printf("올바른 수를 입력해주세요.\n");
                            }
                        }

                        while (1) 
                        {
                            printf("오른손 손가락:\n");
                            scanf("%d", &user_right_finger);
                            if (user_right_finger >= 0 && user_right_finger <= 4) 
                            {
                                break;
                            }
                            else 
                            {
                                printf("올바른 수를 입력해주세요.\n");
                            }
                        }

                        //아래 각줄 오른쪽에 소스를 보는 사람이 바로 이해 할 수 있또록  해당하는 주석을 꼭 달 것.
                        if (   (user_left_finger + user_right_finger) != (user_left + user_right)    //
                            || (user_left_finger == user_right && user_right_finger == user_left)    //
                            || (user_left_finger == user_left  && user_right_finger == user_right))  //
                        {
                            printf("불가능한 나누기입니다.\n\n");
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
                        printf("COMPUTER의 승리입니다.\n\n\n");  //USER의 차례에서는 COMPUTER의 승리가 있을 수 없는 일.
                        break;
                    }
                    else
                    {
                        printf("USER의 승리입니다.\n\n\n");
                        break;
                    }
                }
                turn = 1;
            }
            else 
            {
                printf("\n\nCOMPUTER 차례입니다.\n");
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
                                printf("COMPUTER는 [왼손으로] USER의 [왼손]을 <공격>하였습니다.\n\n");
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
                                printf("COMPUTER는 [오른손으로] USER의 [왼손]을 <공격>하였습니다.\n\n");
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
                                printf("COMPUTER는 [왼손으로] USER의 [오른손]을 <공격>하였습니다.\n\n");
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
                                printf("COMPUTER는 [오른손으로] USER의 [오른손]을 <공격>하였습니다.\n\n");
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
                    printf("COMPUTER는 <나누기> 행동을 하였습니다.\n\n");
                    while (1) 
                    {
                        dividefinger = divide_finger();
                        if (dividefinger == 0)
                        {
                            //아래의 로직을 보면, 어떤 경우에도 Continue 이므로 조건문이 필요 없음. 그냥 아래 Logic 다 지우고 continue만 하면 됨.
                            //continue도 필요 없음. 자동으로 while문 처음으로 가기 때문에
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
                            if ((com_left + com_right) == 4)  //()로 묶어줌.
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
                            //아래의 로직을 보면, 어떤 경우에도 Continue 이므로 조건문이 필요 없음. 그냥 아래 Logic 다 지우고 continue만 하면 됨.
                            //continue도 필요 없음. 자동으로 while문 처음으로 가기 때문에
                            if ((com_left + com_right) == 1)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 2)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 3)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 4)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 2)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 3)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 4)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 5)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 3)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 4)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 5)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 6)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 4)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 5)  //()로 묶어줌.
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
                            if ((com_left + com_right) == 6)  //()로 묶어줌.
                            {
                                if (com_left != 3 && com_right != 3)
                                {
                                    com_left = 3;
                                    com_right = 3;
                                    break;
                                }
                            }
                        }
                        else if (dividefinger == 19)  //if 앞에 else가 빠져서 추가함.
                        {
                            //아래의 로직을 보면, 어떤 경우에도 Continue 이므로 조건문이 필요 없음. 그냥 아래 Logic 다 지우고 continue만 하면 됨.
                            //continue도 필요 없음. 자동으로 while문 처음으로 가기 때문에
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
                                if (com_left != 4 && com_right != 1 && com_left != 1 && com_right != 4)  //주석 달 것.
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
                                if (com_left != 4 && com_right != 2 && com_left != 2 && com_right != 4)  //주석 달 것.
                                {
                                    com_left = 2;
                                    com_right = 4;
                                    break;
                                }
                            }
                        }
                        else  //불필요한 코딩. else 이하 다 필요없음. 자동으로 while문 처음으로 가기 때문에.
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
                        printf("COMPUTER의 승리입니다.\n\n\n");
                        break;
                    }
                    else
                    {
                        printf("USER의 승리입니다.\n\n\n");  //COMPUTER의 차례에서는 USER의 승리가 있을 수 없는 일.
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
    printf("[COMPUTER의 손가락] 왼손: ");
    finger(com_left);
    printf(" 오른손: ");
    finger(com_right);
    printf("\n");
    printf("[USER의 손가락]     왼손: ");
    finger(user_left);
    printf(" 오른손: ");
    finger(user_right);
    printf("\n===========================================================\n");
}

int judge_divide(int left, int right) 
{
    //오른쪽에 주석 달 것.
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
            printf("■");
        }
        else
        {
            printf("□");
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
    //왼손은 0, 오른손은 1로 정의 <== 쓸데 없는 주석이 있음. 삭제 요망!!!
    int attack = 4;
    //아래에서 값이 뭉게지므로 변수에 초기값 줄 필요 없고, 굳이 불필요하게 변수 선언을 하지 않아도 됨.
    //다음과 같이 하면 됨 => return rand() % 24

    srand(time(NULL));

    attack = rand() % 4;

    return attack;
}

int divide_finger()
{
    int dividefinger = 50;
    //변수명은 단어와 단어 사이를 underscore('_')로 구분해 주는게 좋음. => divide_finger.
    //아래에서 값이 뭉게지므로 변수에 초기값 줄 필요 없고, 굳이 불필요하게 변수 선언을 하지 않아도 됨.
    //다음과 같이 하면 됨 => return rand() % 24

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
void print_status() : 상태창을 출력합니다.

int is_end() : 현 상태의 게임이 종료되었는 지 검사하는 함수입니다. 예를 들어 게임이 종료되었다면 1, 그렇지 않다면 0 을 반환합니다.

char select_action() : COMPUTER 의 차례에서 행동 (공격/나누기)를 결정하는 함수입니다.

int attack() : COMPUTER 가 공격을 선택하였을 때 자신의 어떤 손으로 USER 의 어떤 손을 공격할지 결정하는 함수입니다. 예를 들어 공격 시
가능한 조합은 4 가지이기에 이는 정수형 반환값 0~3 을 통해 구분할
수 있습니다. 단, 젓가락 게임의 규칙을 위반하는 행동은 할 수 없
어야 합니다.

int divide_finger() : COMPUTER 가 나누기를 선택하였을 때 어떻게 나눌 지 결정하는
함수입니다. 예를 들어 나누기 시 가능한 조합은 25 가지이기에 이
는 정수형 반환값 0~24 을 통해 구분할 수 있습니다. 단, 젓가락
게임의 규칙을 위반하는 행동은 할 수 없어야 합니다.
*/

