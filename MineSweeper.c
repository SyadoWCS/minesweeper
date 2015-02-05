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

	//マインスイーパー初期化
	for (x = 0; x <= 12; x++){
		for (y = 0; y <= 12; y++){
			map[y][x] = -1;
		}
	}

	//マインスイーパー地雷チェック初期化
	for (x = 0; x <= 12; x++){
		for (y = 0; y <= 12; y++){
			bombcheck[y][x] = -1;
		}
	}

	//マインスイーパーゲーム開始
	printf("ゲームを開始します。\n");

	//列・行と地雷配置
	printf("列と行を入力してください。(例)5 5(このように列 行の順でそれぞれ最大10まで)\n");
	scanf("%d %d", &xxx, &yyy);

	printf("地雷の数を入力してください(最大8)\n");
	scanf("%d", &bomb);

	//地雷の配置
	for (x = 1; x <= bomb; x++){
		SetBomb();
	}

	while (1){
		DrawMineSweeper();
		printf("選択する列・行を入力してください：\n");
		scanf("%1s", a);
		scanf("%1d", &yy);
		printf("開くならoを、地雷チェックはxを入力してください：\n");
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
				printf("そのマスは開けることができません\n");
			}
			else{
				printf("ゲームオーバー\n");
				break;
			}
		}

		if (strcmp(c, "o") == 0 && map[yy][xx] != -2){
			if (bombcheck[yy][xx] == -3){
				printf("そのマスは開けることができません\n");
			}
			else{
				Open(xx, yy);
			}
		}

		//ゲームクリア判定
		//-1の数を数える
		count = 0;
		for (y = 1; y <= yyy; y++){
			for (x = 1; x <= xxx; x++){
				if (map[y][x] <= -1){
					count++;
				}
			}
		}
		//空のセルを全部開いたらクリア
		if (count == bomb){
			printf("ゲームクリアです！\n");
			break;
		}
	}

	return 0;
}

//マインスイーパー描画
void DrawMineSweeper()
{
	int x, y;

	/* マインスイーパー描画 */
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

//地雷を設置する
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

//開けたマスの周囲の爆弾の数を数える
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