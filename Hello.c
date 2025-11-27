#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<string.h>

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

int main() {
    const char *prompt = "This is our pps project guys.";
    char input[1024];

    printf("Typing Speed Test (simple version)\n");
    printf("----------------------------------\n");
    printf("Type the following sentence and press ENTER:\n\n");
    printf("%s\n\n", prompt);
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

    // End timer
    time_t end = time(NULL);

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
