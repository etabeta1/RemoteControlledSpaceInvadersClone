
/*
 * remote controlled space invader clone for nodemcu 1.0 made by Andrea Oggioni
 */
#include <TVout.h>
#include <fontALL.h>
TVout TV;

#define numberOfEnemies 15
#define maxEnemyMovement 20
#define playerDefaultY 68
#define numberOfBullets 1
#define enemyShootDelay 300

int points = 0;
unsigned long int millisLastEnemyMovement = 0;
unsigned long int millisLastEnemyShoot = 0;
int enemyMovementDelay = 850;
int enemyMovement = 0;
bool directionIsRight = true;
unsigned long int ms = 0;

typedef struct {
    int x;
    int y;
    bool shootable;
} Bullet;

struct p {
    int x;
} player;

typedef struct {
    int x;
    int y;
    bool alive;
} Enemy;

Bullet bullet;
Bullet bulletList[numberOfBullets];
Enemy enemyList[numberOfEnemies];

void renderEnemy(int x, int y)
{
    TV.set_pixel(x + 2, y, WHITE);
    TV.set_pixel(x + 8, y, WHITE);

    TV.set_pixel(x + 3, y + 1, WHITE);
    TV.set_pixel(x + 7, y + 1, WHITE);

    TV.set_pixel(x + 2, y + 2, WHITE);
    TV.set_pixel(x + 3, y + 2, WHITE);
    TV.set_pixel(x + 4, y + 2, WHITE);
    TV.set_pixel(x + 5, y + 2, WHITE);
    TV.set_pixel(x + 6, y + 2, WHITE);
    TV.set_pixel(x + 7, y + 2, WHITE);
    TV.set_pixel(x + 8, y + 2, WHITE);

    TV.set_pixel(x + 1, y + 3, WHITE);
    TV.set_pixel(x + 2, y + 3, WHITE);
    TV.set_pixel(x + 4, y + 3, WHITE);
    TV.set_pixel(x + 5, y + 3, WHITE);
    TV.set_pixel(x + 6, y + 3, WHITE);
    TV.set_pixel(x + 8, y + 3, WHITE);
    TV.set_pixel(x + 9, y + 3, WHITE);

    TV.set_pixel(x, y + 4, WHITE);
    TV.set_pixel(x + 1, y + 4, WHITE);
    TV.set_pixel(x + 2, y + 4, WHITE);
    TV.set_pixel(x + 3, y + 4, WHITE);
    TV.set_pixel(x + 4, y + 4, WHITE);
    TV.set_pixel(x + 5, y + 4, WHITE);
    TV.set_pixel(x + 6, y + 4, WHITE);
    TV.set_pixel(x + 7, y + 4, WHITE);
    TV.set_pixel(x + 8, y + 4, WHITE);
    TV.set_pixel(x + 9, y + 4, WHITE);
    TV.set_pixel(x + 10, y + 4, WHITE);

    TV.set_pixel(x, y + 5, WHITE);
    TV.set_pixel(x + 2, y + 5, WHITE);
    TV.set_pixel(x + 3, y + 5, WHITE);
    TV.set_pixel(x + 4, y + 5, WHITE);
    TV.set_pixel(x + 5, y + 5, WHITE);
    TV.set_pixel(x + 6, y + 5, WHITE);
    TV.set_pixel(x + 7, y + 5, WHITE);
    TV.set_pixel(x + 8, y + 5, WHITE);
    TV.set_pixel(x + 10, y + 5, WHITE);

    TV.set_pixel(x, y + 6, WHITE);
    TV.set_pixel(x + 2, y + 6, WHITE);
    TV.set_pixel(x + 8, y + 6, WHITE);
    TV.set_pixel(x + 10, y + 6, WHITE);

    TV.set_pixel(x + 3, y + 7, WHITE);
    TV.set_pixel(x + 4, y + 7, WHITE);
    TV.set_pixel(x + 6, y + 7, WHITE);
    TV.set_pixel(x + 7, y + 7, WHITE);
}

void renderPlayer(int x, int y)
{
    TV.set_pixel(x + 2, y, WHITE);
    TV.set_pixel(x + 4, y, WHITE);

    TV.set_pixel(x + 2, y + 1, WHITE);
    TV.set_pixel(x + 4, y + 1, WHITE);

    TV.set_pixel(x + 1, y + 2, WHITE);
    TV.set_pixel(x + 2, y + 2, WHITE);
    TV.set_pixel(x + 4, y + 2, WHITE);
    TV.set_pixel(x + 5, y + 2, WHITE);

    TV.set_pixel(x + 1, y + 3, WHITE);
    TV.set_pixel(x + 2, y + 3, WHITE);
    TV.set_pixel(x + 3, y + 3, WHITE);
    TV.set_pixel(x + 4, y + 3, WHITE);
    TV.set_pixel(x + 5, y + 3, WHITE);

    TV.set_pixel(x, y + 4, WHITE);
    TV.set_pixel(x + 1, y + 4, WHITE);
    TV.set_pixel(x + 2, y + 4, WHITE);
    TV.set_pixel(x + 4, y + 4, WHITE);
    TV.set_pixel(x + 5, y + 4, WHITE);
    TV.set_pixel(x + 6, y + 4, WHITE);

    TV.set_pixel(x, y + 5, WHITE);
    TV.set_pixel(x + 2, y + 5, WHITE);
    TV.set_pixel(x + 3, y + 5, WHITE);
    TV.set_pixel(x + 4, y + 5, WHITE);
    TV.set_pixel(x + 6, y + 5, WHITE);

    TV.set_pixel(x, y + 6, WHITE);
    TV.set_pixel(x + 1, y + 6, WHITE);
    TV.set_pixel(x + 2, y + 6, WHITE);
    TV.set_pixel(x + 4, y + 6, WHITE);
    TV.set_pixel(x + 5, y + 6, WHITE);
    TV.set_pixel(x + 6, y + 6, WHITE);

    TV.set_pixel(x + 2, y + 7, WHITE);
    TV.set_pixel(x + 3, y + 7, WHITE);
    TV.set_pixel(x + 3, y + 7, WHITE);
    TV.set_pixel(x + 4, y + 7, WHITE);

    TV.set_pixel(x + 1, y + 8, WHITE);
    TV.set_pixel(x + 2, y + 8, WHITE);
    TV.set_pixel(x + 4, y + 8, WHITE);
    TV.set_pixel(x + 5, y + 8, WHITE);
}

void shoot()
{
    if (bullet.shootable) {
        bullet.shootable = false;
        bullet.x = player.x + 3;
        bullet.y = playerDefaultY;
    }
}

void left()
{
    if (player.x > 0) {
        player.x--;
    }
}

void right()
{
    if (player.x < 110) {
        player.x++;
    }
}

void spriteUpdate()
{
    ms = millis();
    if (!bullet.shootable) {
        bullet.y--;
        if (bullet.y <= 0) {
            bullet.x = -1;
            bullet.y = -1;
            bullet.shootable = true;
        }
    }
    for (int i = 0; i < numberOfEnemies; i++) {
        if (enemyList[i].alive && bullet.x >= enemyList[i].x && bullet.x < enemyList[i].x + 11 && bullet.y > enemyList[i].y && bullet.y < enemyList[i].y + 8) {
            bullet.shootable = true;
            enemyList[i].alive = false;
            points++;
            enemyMovementDelay = round(enemyMovementDelay / 1.6);
        }
    }
    if (ms - millisLastEnemyMovement > enemyMovementDelay) {
        millisLastEnemyMovement = ms;
        if (directionIsRight) {
            enemyMovement++;
            for (int i = 0; i < numberOfEnemies; i++) {
                enemyList[i].x++;
            }
        }
        else {
            enemyMovement--;
            for (int i = 0; i < numberOfEnemies; i++) {
                enemyList[i].x--;
            }
        }
        if (enemyMovement == 0 || enemyMovement == maxEnemyMovement) {
            directionIsRight = !directionIsRight;
            for (int i = 0; i < numberOfEnemies; i++) {
                enemyList[i].y++;
            }
        }
    }
    if(ms - millisLastEnemyShoot > enemyShootDelay){
        millisLastEnemyShoot = ms;
        int Enum, Bnum;
        do{
            Enum = random(numberOfEnemies);
        }while(enemyList[Enum].alive == false);
        for(Bnum = 0; Bnum < numberOfBullets; Bnum++){
            if(bulletList[Bnum].shootable){
                break;
            }
        }
        if(Bnum != numberOfBullets){
          bulletList[Bnum].x = enemyList[Enum].x + 5;
          bulletList[Bnum].y = enemyList[Enum].y + 5;
          bulletList[Bnum].shootable = false;
        }
    }
    for(int i = 0; i < numberOfBullets; i++){
        if(!bulletList[i].shootable){
            bulletList[i].y++;
            if(bulletList[i].y > 97){
                bulletList[i].shootable = true;
            }
            if(bulletList[i].x >= player.x && bulletList[i].x < player.x + 7 && bulletList[i].y >= playerDefaultY && bulletList[i].y < playerDefaultY + 6){
            youLose();
        }
        }
        
    }
    //for(int i = 0; i < numberOfBullets; i++){}
}

void render()
{
    TV.delay_frame(1);
    TV.clear_screen();
    TV.println(0, 90, "punti: ");
    TV.println(40, 82, points);
    if (!bullet.shootable) {
        TV.set_pixel(bullet.x, bullet.y, WHITE);
    }
    for(int i = 0; i < numberOfBullets; i++){
        if(!bulletList[i].shootable){
            TV.set_pixel(bulletList[i].x, bulletList[i].y, WHITE);
        }
    }
    renderPlayer(player.x, playerDefaultY);
    for (int i = 0; i < numberOfEnemies; i++) {
        if (enemyList[i].alive) {
            renderEnemy(enemyList[i].x, enemyList[i].y);
        }
    }
}

void waitNoHLT(unsigned long int ms)
{
    unsigned long int start = millis();
    while (millis() < start + ms);
}

void intro()
{
    TV.select_font(font8x8);
    TV.println(20, 20, "REMOTE");
    TV.println(20, 30, "CONTROLLED");
    TV.println(20, 40, "SPACE");
    TV.println(20, 50, "INVADERS");
    TV.select_font(font6x8);
    TV.println(0, 75, "Creato da");
    TV.println(20, 85, "Andrea Oggioni");
    waitNoHLT(2000);
    for (int i = 0; i < 96; i++) {
        TV.draw_line(0, i, 119, i, INVERT);
        waitNoHLT(5);
    }
    for (int i = 0; i < 96; i++) {
        TV.draw_line(0, i, 119, i, BLACK);
        waitNoHLT(5);
    }
}

void youWin()
{
    TV.clear_screen();
    for (int i = 0; i < 96; i++) {
        TV.draw_line(0, i, 119, i, WHITE);
        waitNoHLT(5);
    }
    for (int i = 0; i < 96; i++) {
        TV.draw_line(0, i, 119, i, BLACK);
        waitNoHLT(5);
    }
    TV.select_font(font8x8);
    TV.println(20, 40, "HAI VINTO");
    while(true);
}
void youLose()
{
    TV.clear_screen();
    for (int i = 0; i < 96; i++) {
        TV.draw_line(0, i, 119, i, WHITE);
        waitNoHLT(5);
    }
    for (int i = 0; i < 96; i++) {
        TV.draw_line(0, i, 119, i, BLACK);
        waitNoHLT(5);
    }
    TV.select_font(font8x8);
    TV.println(20, 40, "HAI PERSO");
    while(true);
}

void setup()
{
    char x;
    Serial.begin(115200);
    randomSeed(analogRead(A0));
    bullet.x = -1;
    bullet.y = -1;
    bullet.shootable = true;
    for(int i = 0; i < numberOfBullets; i++){
        bulletList[i] = {-1, -1, true};
    }
    for (int i = 0; i < 5; i++) {
        enemyList[i] = { 4 + i * 20, 3, true };
        enemyList[i + 5] = { 4 + i * 20, 18, true };
        enemyList[i + 10] = { 4 + i * 20, 33, true };
    }
    player.x = 50;
    pinMode(2, INPUT); //right
    pinMode(3, INPUT); //left
    pinMode(4, INPUT); //shoot
    TV.begin(PAL, 120, 96);
    intro();
    TV.select_font(font6x8);
}

void loop()
{

    //TV.delay_frame(1);
    if (digitalRead(3) == HIGH) {
        left();
    }
    if (digitalRead(2) == HIGH) {
        right();
    }
    if (digitalRead(4) == HIGH) {
        shoot();
    }

    spriteUpdate();
    render();
    if(points >= numberOfEnemies){
        youWin();  
    }
}
