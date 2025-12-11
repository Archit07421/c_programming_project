#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<string.h>
#include <stdlib.h> 

int count_words(const char *str){  
   int count=0;
   int in_word=0;
   while(*str){
     if(isspace((unsigned char )*str)){
       if(in_word){
         count++;
         in_word=0;
       }
     }else{
       in_word=1;
     }
     str++;
   }

   if(in_word){
    count++;
   }

   return count;
}

int calculate_accuracy_simple(const char *prompt, const char *input, int *errors) {
    int i = 0;
    int correct_chars = 0;
    *errors = 0;

    int n_prompt = (int)strlen(prompt);
    int n_input = (int)strlen(input);
    int n_min = n_prompt < n_input ? n_prompt : n_input;

    for (i = 0; i < n_min; ++i) {
        if (prompt[i] == input[i]) {
            correct_chars++;
        } else {
            (*errors)++;
        }
    }

    // Any leftover characters are errors (missing or extra)
    if (n_prompt > n_min) {
        (*errors) += (n_prompt - n_min); // missing chars from input
    } else if (n_input > n_min) {
        (*errors) += (n_input - n_min); // extra chars typed
    }

    return correct_chars;
}



int main() {
    const char *easy_prompt[] = {
        "Typing is a skill that grows stronger with small steps taken every day. ",
        "When you begin, your fingers move slowly, searching for keys one by one. ",
        "but with gentle practice something begins to change. Your hands start to remember movements ",
        "your eyes glide over the text more naturally, and your thoughts connect smoothly with the keyboard. ",
        "Soon typing feels less like effort and more like a flowing rhythm. ",
        "Even a few minutes of practice build improvement, confidence rises, and mistakes slowly fade away. ",
        "Typing is not about perfection — it is about consistency and patience. ",
        "The more you type, the more natural language becomes through your fingertips.",

        "Learning to type is like learning to ride a bicycle — uncertain at first but rewarding later. ",
        "Every day your fingers learn a bit more, your speed increases, and typing becomes automatic. ",
        "Soon you write messages faster, complete homework quicker, and express ideas clearly. ",
        "Typing is a tool of creativity and communication, useful for school, work, and life. ",
        "With discipline and practice, typing becomes a lifelong skill."
    };

    const char *medium_prompt[] = {
        "Typing efficiently is not just moving fingers across keys; it is a collaboration between muscle memory and thought. ",
        "In the early stages each keypress is deliberate, but repetition forms pathways that allow words to appear effortlessly. ",
        "Accuracy strengthens, rhythm forms, and typing becomes an instinct. Eventually you focus on ideas rather than keys, ",
        "and sentences expand naturally. With practice typing becomes both mental and physical training, sharpening thought ",
        "while improving communication and productivity.",

        "Modern communication lives through typing. When your fingers know the keyboard, your mind is free — ",
        "ideas flow without interruption. Assignments complete faster, writing becomes clearer, and creativity grows. ",
        "Typing is more than pressing keys — it is shaping language with rhythm, speed, and precision. ",
        "Every paragraph improves tomorrow's ability."
    };

    const char *hard_prompt[] = {
        "Typing mastery represents a sophisticated integration of perception, coordination, memory, and linguistic reasoning. ",
        "At high levels the typist no longer thinks about keys or even words; ideas flow directly into structured language. ",
        "Neural pathways strengthen, cognitive load decreases, and keystrokes become automatic. ",
        "True mastery appears when clarity remains even at high speed — when intention becomes text with elegant precision.",

        "Expert typing synchronizes cognition with movement. Every sentence reflects countless micro-decisions processed instantly. ",
        "The fingers respond like instruments guided by thought. Mistakes are not failure but feedback, shaping precision over time. ",
        "Eventually awareness moves from keystrokes to ideas — typing becomes a channel through which language flows."
    };

    int easy_count = sizeof(easy_prompt)/sizeof(easy_prompt[0]);
    int medium_count = sizeof(medium_prompt)/sizeof(medium_prompt[0]);
    int hard_count = sizeof(hard_prompt)/sizeof(hard_prompt[0]);

    const char *prompt = NULL;
    char input[1024];
    int choice;
    

   printf("Typing Speed Test (simple version)\n");
    printf("----------------------------------\n");
    printf("Choose difficulty level:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter your choice (1-3): ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    // Clear leftover newline from buffer after scanf
    getchar();

    srand(time(NULL));

    switch (choice) {
        case 1:
            prompt = easy_prompt[rand() % easy_count];
            break;
        case 2:
            prompt = medium_prompt[rand() % medium_count];
            break;
        case 3:
            prompt = hard_prompt[rand() % hard_count];
            break;
        default:
            printf("Invalid choice. Defaulting to Easy mode.\n");
            prompt = easy_prompt[rand() % easy_count];
            break;
    }

    switch (choice) {
        case 1: printf("\nYou selected: Easy\n\n"); 
                break;
        case 2: printf("\nYou selected: Medium\n\n"); 
                break;
        case 3: printf("\nYou selected: Hard\n\n"); 
                break;
        default: printf("\nInvalid number\n\n");
    }

    printf("Type the following text and press ENTER:\n\n");
   printf("\033[36m%s\033[0m\n\n", prompt);


    printf("Press ENTER when you're ready to start...\n");
    getchar();  // wait for user to press Enter before starting

    printf("Start typing now:\n");


    // Start timer
    time_t start = time(NULL);

    // Read what the user types
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

      size_t len = strlen(input);
    while (len > 0 && (input[len-1] == '\n' || input[len-1] == '\r')) {
        input[len-1] = '\0';
        len--;
    }

    
    // End timer
    time_t end = time(NULL);

   int errors = 0;
    int correct_chars = calculate_accuracy_simple(prompt, input, &errors);
    int total_prompt_chars = (int)strlen(prompt);
    double accuracy = 0.0;
    if (total_prompt_chars > 0) {
        accuracy = (double)correct_chars / (double)total_prompt_chars * 100.0;
    }

    printf("\nCorrect characters: %d\n", correct_chars);
    printf("Errors: %d\n", errors);
    printf("Accuracy: %.2f%%\n", accuracy);

   



    // Calculate time taken in seconds
    double seconds = difftime(end, start);
    if (seconds == 0) {
        seconds = 1; // avoid division by zero if it's too fast
    }

    // Count words typed
    int words_typed = count_words(input);

    // Calculate WPM
    double minutes = seconds / 60.0;
    double wpm = words_typed / minutes;

    printf("\nTime taken: %.2f seconds\n", seconds);
    printf("Words typed: %d\n", words_typed);
    printf("Your typing speed: %.2f WPM\n", wpm);

    return 0;
}
