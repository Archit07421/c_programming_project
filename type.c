#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_TYPED 5000
#define MAX_SCORES 200
#define SCORE_FILE "scores.txt"

/* ===== Colored Text ===== */
#define RED   "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

/* -------- LEADERBOARD STRUCT -------- */
typedef struct {
    char name[50];
    char mode[20];
    float wpm;
    float accuracy;
} Score;

/* -------- RANDOM LEGEND TEXT -------- */
void generateLegendText(char *buffer, int length) {
    const char chars[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
        "!@#$%^&*()_+-=[]{}|;:'\",.<>?/`~";
    int total = sizeof(chars) - 1;

    for (int i = 0; i < length; i++) {
        buffer[i] = chars[rand() % total];
        if (rand() % 17 == 0) buffer[i] = ' ';
        if (rand() % 61 == 0) buffer[i] = '\n';
    }
    buffer[length] = '\0';
}

/* -------- SAVE SCORE -------- */
void save_score(const char *player, const char *mode, float wpm, float accuracy) {
    FILE *fp = fopen(SCORE_FILE, "a");
    if (!fp) return;
    fprintf(fp, "%s %s %.2f %.2f\n", player, mode, wpm, accuracy);
    fclose(fp);
}

/* -------- SHOW LEADERBOARD -------- */
void show_leaderboard() {
    FILE *fp = fopen(SCORE_FILE, "r");
    if (!fp) { printf("\nNo scores yet.\n"); return; }

    Score scores[MAX_SCORES];
    int count = 0;

    while (count < MAX_SCORES &&
        fscanf(fp, "%49s %19s %f %f",
               scores[count].name,
               scores[count].mode,
               &scores[count].wpm,
               &scores[count].accuracy) == 4)
    {
        count++;
    }
    fclose(fp);

    if (count == 0) { printf("\nNo scores saved.\n"); return; }

    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (scores[j].wpm > scores[i].wpm) {
                Score t = scores[i]; scores[i] = scores[j]; scores[j] = t;
            }

    printf("\n========== LEADERBOARD ==========\n");
    printf("%-15s %-10s %-8s %-9s\n", "Name", "Mode", "WPM", "Accuracy");
    for (int i = 0; i < count && i < 10; i++)
        printf("%-15s %-10s %-8.2f %-8.2f%%\n",
            scores[i].name, scores[i].mode, scores[i].wpm, scores[i].accuracy);
    printf("=================================\n");
}

/* ==================== MAIN ==================== */
int main() {
    srand(time(NULL));

    char player[50];
    printf("Enter name: ");
    scanf("%49s", player);
    while (getchar()!='\n');

    /* -------- LONG PARAGRAPHS -------- */
    const char *easy[] = {
        "Typing is a skill that grows stronger with small steps taken every day. "
        "When you begin, your fingers move slowly, searching for keys one by one, "
        "but with gentle practice something begins to change. Your hands start to remember movements, "
        "your eyes glide over the text more naturally, and your thoughts connect smoothly with the keyboard. "
        "Soon typing feels less like effort and more like a flowing rhythm. "
        "Even a few minutes of practice build improvement, confidence rises, and mistakes slowly fade away. "
        "Typing is not about perfection — it is about consistency and patience. "
        "The more you type, the more natural language becomes through your fingertips.",

        "Learning to type is like learning to ride a bicycle — uncertain at first but rewarding later. "
        "Every day your fingers learn a bit more, your speed increases, and typing becomes automatic. "
        "Soon you write messages faster, complete homework quicker, and express ideas clearly. "
        "Typing is a tool of creativity and communication, useful for school, work, and life. "
        "With discipline and practice, typing becomes a lifelong skill."
    };

    const char *medium[] = {
        "Typing efficiently is not just moving fingers across keys; it is a collaboration between muscle memory and thought. "
        "In the early stages each keypress is deliberate, but repetition forms pathways that allow words to appear effortlessly. "
        "Accuracy strengthens, rhythm forms, and typing becomes an instinct. Eventually you focus on ideas rather than keys, "
        "and sentences expand naturally. With practice typing becomes both mental and physical training, sharpening thought "
        "while improving communication and productivity.",

        "Modern communication lives through typing. When your fingers know the keyboard, your mind is free — "
        "ideas flow without interruption. Assignments complete faster, writing becomes clearer, and creativity grows. "
        "Typing is more than pressing keys — it is shaping language with rhythm, speed, and precision. "
        "Every paragraph improves tomorrow's ability."
    };

    const char *hard[] = {
        "Typing mastery represents a sophisticated integration of perception, coordination, memory, and linguistic reasoning. "
        "At high levels the typist no longer thinks about keys or even words; ideas flow directly into structured language. "
        "Neural pathways strengthen, cognitive load decreases, and keystrokes become automatic. "
        "True mastery appears when clarity remains even at high speed — when intention becomes text with elegant precision.",

        "Expert typing synchronizes cognition with movement. Every sentence reflects countless micro-decisions processed instantly. "
        "The fingers respond like instruments guided by thought. Mistakes are not failure but feedback, shaping precision over time. "
        "Eventually awareness moves from keystrokes to ideas — typing becomes a channel through which language flows."
    };

    static char legend[4000];
    char mode[20];
    const char *text = NULL;

    int c;
    printf("\nSelect Mode:\n1 Easy\n2 Medium\n3 Hard\n4 Legend ⚡\nChoice: ");
    scanf("%d", &c); while(getchar()!='\n');

    if(c==1){ text=easy[rand()%2]; strcpy(mode,"Easy"); }
    else if(c==2){ text=medium[rand()%2]; strcpy(mode,"Medium"); }
    else if(c==3){ text=hard[rand()%2]; strcpy(mode,"Hard"); }
    else if(c==4){ generateLegendText(legend,3500); text=legend; strcpy(mode,"Legend"); }
    else return printf("Invalid selection.\n"),0;

    int duration;
    printf("\n--- TEXT ---\n\n%s\n\nTime (seconds): ", text);
    scanf("%d",&duration); while(getchar()!='\n');
    printf("\nStart typing below:\n\n");

    char typed[MAX_TYPED]; int len=0,words=0,inword=0;
    time_t start=time(NULL);

    while(time(NULL)-start<duration && len<MAX_TYPED){
        if(kbhit()){
            char ch=getch();
            if(ch=='\b'){ if(len>0){ len--; printf("\b \b");} continue; }
            if(ch=='\r') ch='\n';
            typed[len++]=ch; printf("%c",ch);
            if(ch==' '||ch=='\n'||ch=='\t'){ if(inword){words++;inword=0;} }
            else inword=1;
        }
    }
    if(inword) words++;
    typed[len]='\0';

    printf("\n\nTIME UP!\n");

    float minutes=(float)duration/60.0f;
    float wpm = (minutes>0)? words/minutes:0;
    float wps = (duration>0)? (float)words/duration:0;

    int correct=0, ref_len=strlen(text);
    for(int i=0;i<len && i<ref_len;i++) if(typed[i]==text[i]) correct++;
    float acc = (len>0)? (correct*100.0/len):0;

    printf("\n===== RESULTS =====\n");
    printf("Name  : %s\nMode  : %s\nWords : %d\n", player, mode, words);
    printf("WPM   : %.2f\nWPS   : %.2f\n", wpm,wps);
    printf("Accuracy: %.2f%%\n==============\n",acc);

    /* ===== Colored Mistake Display ===== */
    printf("\nYour Typing:\n\n");
    for(int i=0;i<len || i<ref_len;i++){
        char r=(i<ref_len)?text[i]:'\0';
        char t=(i<len)?typed[i]:'\0';

        if(t=='\n'){ printf("\n"); continue; }

        if(i>=len && r!='\0'){ printf(RED "_" RESET); continue; }

        if(t==r) printf(GREEN "%c" RESET,t);
        else printf(RED "%c" RESET,t);
    }
    printf("\n");

    save_score(player,mode,wpm,acc);
    show_leaderboard();

    printf("\nThanks for playing!\n");
}

