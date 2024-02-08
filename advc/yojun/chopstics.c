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

//손가락을 출력하는 방법은 여러가지(반복문으로 출력, printf formatting으로 출력 등)가 있지만
//배열로 선언해 두고, 직접 접근하는 방법이 가장 효율적이라 판단하여 "char *" 배열을 사용함.
//배열의 인덱스는 0부터 시작하므로, 손가락 개수와 동일하게 맞추기 위해서
//첫번째는 모든 손가락이 접힌상태로 지정하고, 두번째 값부터 펼친 손가락을 나열함.
//따라서, 배열요소의 총 개수는 6개(손가락수 5개 + NULL)임.
static char *open_finger[6] = {
    "□□□□□",  //0
    "■□□□□",  //1
    "■■□□□",  //2
    "■■■□□",  //3
    "■■■■□",  //4
    "■■■■■"   //5
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
            input = choice_char("새로운 게임을 시작할까요? [Y or N]\n", 'Y', 'N');
            if (input == 'Y')
            {
                printf("\n게임이 시작되었습니다.\n");
                break;
            }
            else if (input == 'N')
            {
                printf("\n게임을 종료합니다.\n");
                exit(0);
            }
            else
            {
                printf("\n올바르지 않은 명령어입니다.\n\n");
            }
        }  //End of while

        //예시의 순서와 동일하게 컴퓨터 왼손/오른손, USER 왼손/오른손 순으로 인자를 설정함.
        print_status(com_l_finger, com_r_finger, user_l_finger, user_r_finger);

        //최초 공격자를 랜덤으로 선택함.
        turn = get_random_number(0, 1);
        printf("turn=[%d]-[%s]\n", turn, turn == TURN_COM ? "COMPUTER" : "USER");

        while (1)
        {
            if (turn == TURN_USER)  //USER 차례
            {
                sel_atk_div = choice_char("USER 차례입니다.\n어떤 행동을 하시겠습니까? [A:공격 D:나누기]\n", 'A', 'D');

                if (sel_atk_div == 'A')  //공격
                {
                    sel_atk_user_hand = choice_char("어느 손으로 공격하시겠습니까? [L:왼손 R:오른손]\n", 'L', 'R');
                    printf("sel_atk_user_hand=[%c]\n", sel_atk_user_hand);

                    sel_com_hand = choice_char("상대방의 어느 손을 공격하시겠습니까? [L:왼손 R:오른손]\n", 'L', 'R');
                    printf("sel_com_hand=[%c]\n", sel_com_hand);

                    if (sel_com_hand == 'L')  //COMPUTER의 왼손을 공격하는 경우
                    {
                        if (sel_atk_user_hand == 'L')  //USER의 손이 왼손인 경우.
                        {
                            com_l_finger += user_l_finger;  //COMPUTER의 왼손에 USER의 왼손 펼친 손가락 개수를 더한다.
                        }
                        else  //'R'-USER의 손이 오른손인 경우
                        {
                            com_l_finger += user_r_finger;  //COMPUTER의 왼손에 USER의 오른손 펼친 손가락 개수를 더한다.
                        }
                    }
                    else  //sel_com_hand == 'R'. COMPUTER의 오른손을 공격하는 경우. choice_char 함수에서는 'L', 'R'값 반환을 보장하므로 else면 무조건 'R'이라고 보면 됨.
                    {
                        if (sel_atk_user_hand == 'L')  //왼손
                        {
                            com_r_finger += user_l_finger;  //COMPUTER의 오른손에 USER의 왼손 펼친 손가락 개수를 더한다.
                        }
                        else  //'R'-오른손
                        {
                            com_r_finger += user_r_finger;  //COMPUTER의 오른손에 USER의 오른손 펼친 손가락 개수를 더한다.
                        }
                    }

                    ret = is_end(com_l_finger, com_r_finger);
                    if (ret == 0)  //COMPUTER의 왼손, 오른손의 손가락이 모두 펼쳐진 경우.
                    {
                        printf("USER의 승리입니다.\n");
                        break;  //프로그램의 맨 처음으로 돌아감.
                    }
                }
                else if (sel_atk_div == 'D')  //나누기
                {
                    while (1)
                    {
                        printf("어떻게 나누시겠습니까? (0이상~4이하의 정수를 입력해주세요.)\n");
                        input_l_finger = choice_num("왼손 손가락:\n",   MIN_FINGER, MAX_FINGER);
                        input_r_finger = choice_num("오른손 손가락:\n", MIN_FINGER, MAX_FINGER);

                        ret = check_divide_rule();
                        if (ret != 0)
                        {
                            printf("불가능한 나누기 입니다.\n");
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
                        //USER 차례 처음으로 다시 되돌아 감.
                        continue;
                    }

                    //차례를 바꿈. => turn을 바꾸지 않아도 자연스럽게 흘러서 turn이 바뀜.
                    //turn = !turn;  //NOT(!) 연산자를 사용하면 1(USER)과 0(COMPUTER)로 toggle 됨.
                    //continue;  //굳이 continue를 하지 않아도 아래에서 turn이 바뀌고 while문의 처음으로 돌아감.
                }
            }
            else  //컴퓨터 차례(TURN_COM)
            {
                printf("COMPUTER 차례입니다.\n");

                sel_atk_div = select_action();
                sel_result  = attack();

                //0: 왼손으로   USER의 왼손   공격
                //1: 왼손으로   USER의 오른손 공격
                //2: 오른손으로 USER의 왼손   공격
                //3: 오른손으로 USER의 오른손 공격
                if (sel_atk_div == 'A')  //공격
                {
                    if (sel_result == '0')              //COMPUTER의 왼손으로 USER의 왼손을 공격하는 경우
                    {
                        user_l_finger += com_l_finger;  //USER의 왼손에 COMPUTER의 왼손 펼친 손가락 개수를 더한다.
                    }
                    else if (sel_result == '1')         //COMPUTER의 왼손으로 USER의 오른손을 공격하는 경우
                    {
                        user_r_finger += com_l_finger;  //USER의 왼손에 COMPUTER의 오른손 펼친 손가락 개수를 더한다.
                    }
                    else if (sel_result == '2')         //COMPUTER의 오른손으로 USER의 왼손을 공격하는 경우
                    {
                        user_l_finger += com_r_finger;  //USER의 오른손에 USER의 오른손 펼친 손가락 개수를 더한다.
                    }
                    else if (sel_result == '3')         //COMPUTER의 오른손으로 USER의 오른손을 공격하는 경우
                    {
                        user_r_finger += com_r_finger;  //USER의 왼손에 COMPUTER의 오른손 펼친 손가락 개수를 더한다.
                    }

                    ret = is_end(user_l_finger, user_r_finger);
                    if (ret == 0)  //COMPUTER의 왼손, 오른손의 손가락이 모두 펼쳐진 경우.
                    {
                        printf("COMPUTER의 승리입니다.\n");
                        break;  //프로그램의 맨 처음으로 돌아감.
                    }
                }
                else if (sel_atk_div == 'D')  //나누기
                {
                    sel_result = divide_finger();

                    //차례를 바꿈.
                    turn = !turn;  //NOT(!) 연산자를 사용하면 1(USER)과 0(COMPUTER)로 toggle 됨.
                    continue;
                }
            }
        
            //차례를 바꿈.
            turn = !turn;  //0과 1의 toggle 처리(NOT으로 구현)
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
        printf("난수범위의 최소값은 최대값보다 작아야 합니다.\n");
        return -1;
    }

    range = range_max - range_min + 1;

    srand((unsigned int)time(NULL));

    return rand() % range;
}

//숫자를 입력받아 반환하는 함수.
// - question : 질문 String. 값을 잘못 입력했을때, 질문까지 같이 반복하도록 인자로 받음.
// - min_num  : 최소값
// - max_num  : 최대값
int
choice_num(char *question, int min_num, int max_num)
{
    int  c, number;

    while (1)
    {
        printf(question);
        scanf("%d", &number);
        while(c = fgetc(stdin) != '\n' && c != EOF);  //Carriage Return 문자 또는 EOF가 아니면 모두 flush 처리.

        if (number >= min_num && number <= max_num)  //범위 내의 숫자만 입력받도록 처리.
        {
            break;
        }

        printf("올바른 수를 입력해 주세요.\n");
    }

    return number;
}

//문자를 입력받아 반환하는 함수.
// - question : 질문 String. 값을 잘못 입력했을때, 질문까지 같이 반복하도록 인자로 받음.
// - sel1 : 필수입력문자1
// - sel2 : 필수입력문자2
char
choice_char(char *question, char sel1, char sel2)
{
    int  c;
    char character;

    while (1)
    {
        printf(question);
        scanf("%c", &character);
        while(c = fgetc(stdin) != '\n' && c != EOF);  //Carriage Return 문자 또는 EOF가 아니면 모두 flush 처리.

        if (character == sel1 || character == sel2)  //정해진 값이 입력되지 않으면, 다시 입력 받도록 처리.
        {
            break;
        }
        else
        {
            printf("올바른 수를 입력해 주세요.\n");
        }
    }

    return character;
}

//상태창을 출력합니다.
void
print_status(int u_left, int u_right, int c_left, int c_right)
{
  printf("===========================================================\n");
  printf("[COMPUTER의 손가락] 왼손: %s 오른손: %s\n", open_finger[c_left], open_finger[c_right]);
  printf("[USER의 손가락]     왼손: %s 오른손: %s\n", open_finger[u_left], open_finger[u_right]);
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
    if (left_finger_cnt >= FINGER_CNT && right_finger_cnt >= FINGER_CNT)  //왼손, 오른손의 손가락이 모두 펼쳐진 경우.
    {
        return 0;
    }

    return -1;
}

//COMPUTER 의 차례에서 행동 (공격/나누기)를 결정하는 함수입니다.
char
select_action()
{
    int  ret = 0;
    char sel_atk_div;

    //COMPUTER 차례입니다. 어떤 행동을 하시겠습니까? [A:공격 D:나누기]
    //공격/나누기 Random 처리.
    ret = get_random_number(0, 1);  //두가지 경우
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
        printf("get_random_number 호출 오류입니다. 프로그램 확인이 필요합니다. ret=[%d]\n", ret);
        exit(-1);
    }
    
    printf("sel_atk_div = [%c]\n", sel_atk_div);

    return sel_atk_div;
}

//COMPUTER 가 공격을 선택하였을 때 자신의 어떤 손으로 USER 의
//어떤 손을 공격할지 결정하는 함수입니다. 예를 들어 공격 시 가능
//한 조합은 4 가지이기에 이는 정수형 반환값 0~3 을 통해 구분할
//수 있습니다. 단, 젓가락 게임의 규칙을 위반하는 행동은 할 수 없
//어야 합니다.
int
attack()
{
    int ret = 0;

    //0: 왼손으로   USER의 왼손   공격
    //1: 왼손으로   USER의 오른손 공격
    //2: 오른손으로 USER의 왼손   공격
    //3: 오른손으로 USER의 오른손 공격
    ret = get_random_number(0, 3);
    if (ret < 0 || ret > 3)
    {
        printf("결과값이 유효하지 않습니다. ret=[%d]\n", ret);
        exit(-1);
    }

    return 0;
}

//COMPUTER 가 나누기를 선택하였을 때 어떻게 나눌 지 결정하는
//함수입니다. 예를 들어 나누기 시 가능한 조합은 25 가지이기에 이
//는 정수형 반환값 0~24 을 통해 구분할 수 있습니다. 단, 젓가락
//게임의 규칙을 위반하는 행동은 할 수 없어야 합니다.
int
divide_finger()
{
    int ret = 0;

    ret = get_random_number(0, 24);

    return 0;
}
