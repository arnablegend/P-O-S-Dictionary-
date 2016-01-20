/*Program to to read a sentence from user and print the parts of speech of each of its constituents
* Reading from file....Done(Partially)
* Storing in a TRIE....Done
* Retrieving from TRIE....Done
* Parsing the string....Done
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct trienode{
    int val;
    struct trienode* linkarr[26];
}node;
int j;
//node* head=NULL;

inline node* create_node(){
    node* ptrsub=(node*)malloc(sizeof(node));
    ptrsub->val=0;
    int i;
    for(i=0;i<26;i++){
        ptrsub->linkarr[i]=NULL;
    }
    j++;
    //printf("  Created");
    return ptrsub;
}
void display_parts_of_speech(int val){
    printf("..Found..");
    char arr[12][14]={"","Indeterminate","Noun","Verb","Adjective","Adverb","Conjuction","Preposition","Interjection","Pronoun","Article","Nominative"};
    printf("%s",arr[val]);
}
void populate(node* root,char* arr,int length,int depth,int sto){
    int i=(int)arr[depth];

    i-=97;
    //printf("\n%d",i);
    if(root->linkarr[i]==NULL)
        root->linkarr[i]=create_node();
    depth++;
    if(depth==length){
        root->linkarr[i]->val=sto;
        //printf("\n");
    }else
        populate(root->linkarr[i],arr,length,depth,sto);
}
void retrieve(char* search_str,node* root,int length,int depth){
    int i=(int)search_str[depth];
    i=i-97;
    if(root->linkarr[i]==NULL){
        printf("..Not found");
        return;
    }
    depth++;
    if(depth==length){
        if(root->linkarr[i]->val)
            display_parts_of_speech(root->linkarr[i]->val);
        else
            printf("..Not Found");
        return;
    }
    retrieve(search_str,root->linkarr[i],length,depth);
}
inline int strlen(char* arr){
    int len=0;
    while(arr[len]!='\0')
        len++;
    return len;
}
inline int strcmp(char* str1,char* str2){
    if(strlen(str1)!=strlen(str2))
        return 0;
    int len=strlen(str1);
    while(len>0){
        len--;
        if(str1[len]!=str2[len])
            return 0;
    }
    return 1;
}
inline void to_lower(char* arr,int length){
    length--;
    while(length>=0){
        if(arr[length]>=65 && arr[length]<=91)
            arr[length]=arr[length]+32;
        length--;
    }
    //printf("\nAccessed");
}
void parse_and_search(char* arr,node* root){
    int index=0,count=0;
    char temp_arr[30],c=arr[index];
    while(index<=strlen(arr)){

        if(c>=91 && c<=125){
            temp_arr[count++]=c;
        }else{
            temp_arr[count]='\0';
            count=0;
            if(strlen(temp_arr)!=0){
                printf("\n%s",temp_arr);
                retrieve(temp_arr,root,strlen(temp_arr),0);

            }
        }
        index++;
        c=arr[index];
    }
}

int char_at(char *str,char c){
    int len=strlen(str);
    int index=0;
    while(index<len){
        if(str[index]==c)
            return index;
        index++;
    }
    return -1;
}
int main(){
    j=0;
    node* root=create_node();
//    char content[7][10]={"what","where","why","who","which","whoami","whatthe"};
    int i=0;
//    for(i=0;i<7;i++){
//        //printf("\n%d",strlen(content[i]));
//        populate(root,content[i],strlen(content[i]),0);
//    }
//    retrieve("where",root,strlen("where"),0);
/****************************************/
    FILE* fp;
    fp=fopen("US.dic","r+");
    char temp_arr[50],c;
    int count=0;
    int total_count=0;
    int line_number=1;
    printf("\nreading from file and populating trie\n");
    while(!feof(fp)){
        c=getc(fp);
        if(c=='\n'){
            line_number++;
            //printf("\n%d",line_number);
            temp_arr[count]='\0';
            count=0;
            to_lower(temp_arr,strlen(temp_arr));
            populate(root,temp_arr,strlen(temp_arr),0,1);
            total_count++;
        }else
            temp_arr[count++]=c;
        if(total_count>=10000){
            printf(".");
            total_count=0;
        }
        //printf("%c",c);
    }
    fclose(fp);
    printf("\nDone..");
/***************************************/
    int index;
    int flag=1;
    count=0;
    total_count=0;
    line_number=1;
    printf("\nreading from 2nd file and populating trie\n");
    fp=fopen("mobyposi.i","r+");
    while(!feof(fp)){
        c=getc(fp);
        //printf("\n%d",c);
        if(c=='\r'){
            line_number++;
            temp_arr[count]='\0';
            if(flag){
                index=char_at(temp_arr,'|');
                if(index!=-1){
                    to_lower(temp_arr,index);
                    if(temp_arr[index+1]=='N')
                        i=2;
                    else if(temp_arr[index+1]=='p')
                        i=2;
                    else if(temp_arr[index+1]=='h')
                        i=2;
                    else if(temp_arr[index+1]=='V')
                        i=3;
                    else if(temp_arr[index+1]=='t')
                        i=3;
                    else if(temp_arr[index+1]=='i')
                        i=3;
                    else if(temp_arr[index+1]=='A')
                        i=4;
                    else if(temp_arr[index+1]=='v')
                        i=5;
                    else if(temp_arr[index+1]=='C')
                        i=6;
                    else if(temp_arr[index+1]=='P')
                        i=7;
                    else if(temp_arr[index+1]=='!')
                        i=8;
                    else if(temp_arr[index+1]=='r')
                        i=9;
                    else if(temp_arr[index+1]=='D')
                        i=10;
                    else if(temp_arr[index+1]=='I')
                        i=10;
                    else if(temp_arr[index+1]=='o')
                        i=11;
                    else
                        i=1;
                    temp_arr[index]='\0';
                    //if(strcmp(temp_arr,"quick"))
                    //    printf("%d,%d\n",line_number,i);
                    populate(root,temp_arr,index,0,i);
                    total_count++;
                    //printf("%s",temp_arr);
                    //printf("%d ",total_count);
                }else{
                    printf("\nError");
                }
            }
            count=0;
            flag=1;
            //printf("\nSet");
        }else{
            if(!((c>=65 && c<=91) || (c>=97 && c<=122) || c=='|' || c=='!')){
                //printf("\nReset");
                flag=0;
            }

            temp_arr[count++]=c;
        }
        if(total_count>10000){
            total_count=0;
            printf(".");
        }
    }
    fclose(fp);
    //printf("The total number of words- %d",total_count);
    printf("\nDone\n");
/***************************************/
    printf("The number of nodes is %d and %d bytes",j,j*108);
    printf("\nEnter text- ");
    char s[1000];
    gets(s);
    to_lower(s,strlen(s));
    parse_and_search(s,root);
    return 0;
}
