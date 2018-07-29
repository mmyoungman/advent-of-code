#include "lib-mmy.h"

int main() {
    FILE* fp = fopen("input", "r");

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(fsize + 1);
    fread(buffer, fsize, 1, fp);
    fclose(fp);

    int numLines;
    char** data = str_split(buffer, '\n', &numLines);
    numLines--;

    //data[0] = "<{!>}>";

    //dbg("%s", data[0]);
    int score = 0;
    int depth = 0;
    int rubbish = 0;
    int rubbishCount = 0;

    for(int i = 0; i < str_len(data[0]); i++) {
        assert(depth >= 0);
        if(data[0][i] == '!') {
                i++;
                continue;
        } 
        
        if(rubbish) {
            if(data[0][i] == '>') {
                rubbish = 0;
                continue;
            }
            rubbishCount++;
            continue;
        } 
        
        if(data[0][i] == '<') {
            rubbish = 1;
            continue;
        }
        
        if(data[0][i] == '{') {
            depth++;
            score += depth;
        } else if(data[0][i] == '}') {
            depth--;
        }
    }
    dbg("9a solution score: %d", score);
    dbg("9b solution rubbish count: %d", rubbishCount);
}
