#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DrawMineSweeper();
void SetBomb();
int Open(int xx, int yy);
int map[12][12];
int bombcheck[12][12];
int xxx, yyy,bomb;

int main(void)
{
	char a[126],c[126];
	int x,y,xx,yy,count;

	//�}�C���X�C�[�p�[������
	for (x = 0; x <= 12; x++){
		for (y = 0; y <= 12; y++){
			map[y][x] = -1;
		}
	}

	//�}�C���X�C�[�p�[�n���`�F�b�N������
	for (x = 0; x <= 12; x++){
		for (y = 0; y <= 12; y++){
			bombcheck[y][x] = -1;
		}
	}

	//�}�C���X�C�[�p�[�Q�[���J�n
	printf("�Q�[�����J�n���܂��B\n");

	//��E�s�ƒn���z�u
	printf("��ƍs����͂��Ă��������B(��)5 5(���̂悤�ɗ� �s�̏��ł��ꂼ��ő�10�܂�)\n");
	scanf("%d %d", &xxx, &yyy);

	printf("�n���̐�����͂��Ă�������(�ő�8)\n");
	scanf("%d", &bomb);

	//�n���̔z�u
	for (x = 1; x <= bomb; x++){
		SetBomb();
	}

	while (1){
		DrawMineSweeper();
		printf("�I�������E�s����͂��Ă��������F\n");
		scanf("%1s", a);
		scanf("%1d", &yy);
		printf("�J���Ȃ�o���A�n���`�F�b�N��x����͂��Ă��������F\n");
		scanf("%1s", c);
	    
		if (strcmp(a, "a") == 0){
			xx = 1;
		}
		else if (strcmp(a, "b") == 0){
			xx = 2;
		}
		else if (strcmp(a, "c") == 0){
			xx = 3;
		}
		else if (strcmp(a, "d") == 0){
			xx = 4;
		}
		else if (strcmp(a, "e") == 0){
			xx = 5;
		}
		else if (strcmp(a, "f") == 0){
			xx = 6;
		}
		else if (strcmp(a, "g") == 0){
			xx = 7;
		}
		else if (strcmp(a, "h") == 0){
			xx = 8;
		}
		else if (strcmp(a, "i") == 0){
			xx = 9;
		}
		else if (strcmp(a, "j") == 0){
			xx = 10;
		}

		yy = yy + 1;

		if (strcmp(c, "x") == 0){
			if (bombcheck[yy][xx] == -1){
				bombcheck[yy][xx] = -3;
			}
			else if (bombcheck[yy][xx] == -3){
				bombcheck[yy][xx] = -1;
			}
			
		}

		if (map[yy][xx] == -2 && strcmp(c, "o") == 0){
			if (bombcheck[yy][xx] == -3){
				printf("���̃}�X�͊J���邱�Ƃ��ł��܂���\n");
			}
			else{
				printf("�Q�[���I�[�o�[\n");
				break;
			}
		}

		if (strcmp(c, "o") == 0 && map[yy][xx] != -2){
			if (bombcheck[yy][xx] == -3){
				printf("���̃}�X�͊J���邱�Ƃ��ł��܂���\n");
			}
			else{
				Open(xx, yy);
			}
		}

		//�Q�[���N���A����
		//-1�̐��𐔂���
		count = 0;
		for (y = 1; y <= yyy; y++){
			for (x = 1; x <= xxx; x++){
				if (map[y][x] <= -1){
					count++;
				}
			}
		}
		//��̃Z����S���J������N���A
		if (count == bomb){
			printf("�Q�[���N���A�ł��I\n");
			break;
		}
	}

	return 0;
}

//�}�C���X�C�[�p�[�`��
void DrawMineSweeper()
{
	int x, y;

	/* �}�C���X�C�[�p�[�`�� */
	printf("  ");
	for (x = 'a'; x <= 'a' + xxx - 1; x++){
		printf("%c ", x );
	}
	printf("\n");
	for (y = 1; y <= yyy; y++) {
		printf("%d ", y-1);
		for (x = 1; x <= xxx; x++) {
			if (map[y][x] >= 0) {
				printf("%d ", map[y][x]);
			}
			else if (bombcheck[y][x] == -3){
				printf("x ");
			}
			else
			{
				printf("? ");
			}
		}
		printf("\n");
	}
}

//�n����ݒu����
void SetBomb()
{
	int x, y;
	x = rand() % xxx + 1;
	y = rand() % yyy + 1;
	if (map[y][x] != -2){
		map[y][x] = -2;
	}
	else{
		SetBomb();
	}
}

//�J�����}�X�̎��͂̔��e�̐��𐔂���
int Open(int xx, int yy){

	int bombcount = 0;

	if (xx >= 1 && xx <= xxx && yy >= 1 && yy <= yyy && map[yy][xx] == -1){
		if (map[yy - 1][xx - 1] == -2){
			bombcount++;
		}
		else if (map[yy - 1][xx] == -2){
			bombcount++;
		}
		else if (map[yy - 1][xx] == -2){
			bombcount++;
		}
		else if (map[yy - 1][xx + 1] == -2){
			bombcount++;
		}
		else if (map[yy][xx - 1] == -2){
			bombcount++;
		}
		else if (map[yy][xx + 1] == -2){
			bombcount++;
		}
		else if (map[yy + 1][xx - 1] == -2){
			bombcount++;
		}
		else if (map[yy + 1][xx] == -2){
			bombcount++;
		}
		else if (map[yy + 1][xx + 1] == -2){
			bombcount++;
		}
		map[yy][xx] = bombcount;

		if (bombcount == 0)
		{
			Open(xx, yy - 1);
			Open(xx, yy + 1);
			Open(xx - 1, yy);
			Open(xx + 1, yy);
			Open(xx - 1, yy - 1);
			Open(xx + 1, yy + 1);
			Open(xx - 1, yy + 1);
			Open(xx + 1, yy - 1);
		}
	}
	return 1;
}