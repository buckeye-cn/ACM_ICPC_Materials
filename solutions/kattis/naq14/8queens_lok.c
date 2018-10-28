#include<stdio.h>

void main()
{
    int pos[64][2];
    short invalid = 0;
    int i;
    int queen_count = 0;
    for (i = 0;i < 8;i++)
    {
        char line[8];
        int j;
        scanf("%s", &line);
        
        for (j = 0;j < 8; j++)
        {
            if (line[j] == '*')
            {
                pos[queen_count][0] = i;
                pos[queen_count][1] = j;
                queen_count++;
            }
        }
    }
        
    if (queen_count != 8) invalid = 1;
    
    i = 0;
    for(i = 0;i < 8 && !invalid;i++)
    {
        int j;
        for (j = i+1;j < 8 && !invalid;j++) invalid = pos[i][0] == pos[j][0] || pos[i][1] == pos[j][1] || pos[i][0]-pos[j][0] == pos[i][1]-pos[j][1] || pos[i][0]+pos[i][1] == pos[j][0]+pos[j][1];
    }

    if (invalid) printf("invalid");
    else printf("valid");
}
