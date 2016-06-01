#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int list1[6][17]={0};
int step[5]={0};
string action("Ω–øÔæ‹¶Ê∞ (1.¬YªÎ§l 2.≤q≥ÊΩ¸µ≤™G 3.≤q≥Ã´·µ≤™G)");
string guess("Ω–§U™`(1.A 2.B 3.C 4.D 5.E)");
string A("   A:");
string B("   B:");
string C("   C:");
string D("   D:");
string E("   E:");
string P1("P1  ");
string P2("P2  ");
string P3("P3  ");
string P4("P4  ");
string splayer("Player");
string turn("'s turn");
string swinner("Winner is player");
int color=0;
int dice=0;
int movetime[5];
int site[5];
int round=0;
int moving[5]={0};
int num_moving=0;
int counter=0;
int player=1;
int choose[5]={0};
int finalchoose[5]={0};
int money[5]={0};
int repeat[5]={0};
int finalrepeat[5]={0};
bool exiting=false;

void print()
{
    system("CLS");
    cout<<"round:"<<round<<endl;
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<17;j++)
        {
            if(j==15&&i<5)
            {
                cout<<"| ";
            }
            else if(list1[i][j]==0)
            {
                cout<<"  ";
            }
            else if(list1[i][j]==16)
            {
                cout<<"A ";
            }
            else if(list1[i][j]==17)
            {
                cout<<"B ";
            }
            else if(list1[i][j]==18)
            {
                cout<<"C ";
            }
            else if(list1[i][j]==19)
            {
                cout<<"D ";
            }
            else if(list1[i][j]==20)
            {
                cout<<"E ";
            }
            else
            {
                if(list1[i][j]>=10)
                {
                    cout<<list1[i][j]-10;
                }
                else
                {
                    cout<<list1[i][j];
                }
                cout<<" ";
            }
        }
        if(i==0)
        {
            cout<<A<<step[i];
        }
        if(i==1)
        {
            cout<<B<<step[i];
        }
        if(i==2)
        {
            cout<<C<<step[i];
        }
        if(i==3)
        {
            cout<<D<<step[i];
        }
        if(i==4)
        {
            cout<<E<<step[i];;
        }
        cout<<endl;
    }
    cout<<P1<<P2<<P3<<P4<<endl;
    for(int i=1;i<5;i++)
    {
        cout<<money[i];
        if(money[i]>=10)
        {
            cout<<"  ";
        }
        else
        {
            cout<<"   ";
        }
    }
    cout<<endl;
    for(int i=1;i<5;i++)
    {
        if(choose[i]==0)
        {
            cout<<"    ";
        }
        else if(choose[i]==16)
        {
            cout<<"A   ";
        }
        else if(choose[i]==17)
        {
            cout<<"B   ";
        }
        else if(choose[i]==18)
        {
            cout<<"C   ";
        }
        else if(choose[i]==19)
        {
            cout<<"D   ";
        }
        else if(choose[i]==20)
        {
            cout<<"E   ";
        }
    }
    cout<<endl;
    for(int i=1;i<5;i++)
    {
        if(finalchoose[i]==0)
        {
            cout<<"   ";
        }
        else if(finalchoose[i]==16)
        {
            cout<<"A   ";
        }
        else if(finalchoose[i]==17)
        {
            cout<<"B   ";
        }
        else if(finalchoose[i]==18)
        {
            cout<<"C   ";
        }
        else if(finalchoose[i]==19)
        {
            cout<<"D   ";
        }
        else if(finalchoose[i]==20)
        {
            cout<<"E   ";
        }
    }
    cout<<endl;
}
void calculate()
{
    int maxsite=0;
    for(int i=0;i<5;i++) //find leader's site
    {
        if(site[i]>maxsite)
        {
            maxsite=site[i];
        }
    }
    int leader=0;
    for(int i=0;i<5;i++)    //find leader
    {
        if(list1[i][maxsite]!=0)
        {
            leader=list1[i][maxsite];
            break;
        }
    }
    for(int i=1;i<5;i++)    //count the money
    {
        if(choose[i]!=0)
        {
            if(choose[i]==leader) //guess right
            {
                money[i]=money[i]+5-repeat[i];
            }
            else                    //guess wrong
            {
                money[i]--;
            }
        }
    }


    counter=0;                      //reset the items
    round++;
    for(int i=0;i<5;i++)
    {
        step[i]=0;
        choose[i]=0;
        repeat[i]=0;
    }
    print();                        //print
}
void roll()                   //roll a die
{
            color=rand()%5;             //choose the color
            if(movetime[color]==round)  //color is used
            {
                roll();                  //choose the color again
                return;                 //return and not to run code below
            }
            movetime[color]++;          //the color is set to be used
            counter++;                  //increase number of dice that have been thrown
            step[color]=rand()%3+1;     //choose the steps that the die should run
            moving[5]={0};              //camels that should move
            num_moving=0;               //numbers of camel that should move
            //if(round!=0)
            //{
                for(int i=4;i>=0;i--)   //remove the site before
                {
                    if(list1[i][site[color]]==16+color)        //find the site before
                    {
                        moving[num_moving]=list1[i][site[color]];
                        list1[i][site[color]]=0;
                        num_moving++;
                    }
                    else if(list1[i][site[color]]!=0&&num_moving!=0)    //find the camel that should be carried
                    {
                        moving[num_moving]=list1[i][site[color]];
                        list1[i][site[color]]=0;
                        num_moving++;
                    }
                }
            //}
            site[color]=site[color]+step[color];        //new site
            if(site[color]>=15)                     //over the finish line
            {

                site[color]=16;
                exiting=true;                       //exit
            }
            for(int i=4;i>=0;i--)                   //find the right site that should be put
            {
                if(list1[i][site[color]]!=0)        //wrong site
                {
                    continue;
                }
                //if(round!=0)
                //{
                    for(int j=0;j<num_moving;j++)
                    {
                        list1[i-j][site[color]]=moving[j];  //put the camels in right site by sequence
                        site[moving[j]-16]=site[color];     //update the new camel site
                    }
                //}
                //else
                //{
                //    list1[i][site[color]]=16+color;
                //}
                print();                                    //print
                break;
            }
        if(counter==5)                                      //one round is over
        {
            system("pause");
            calculate();                                    //calculate player's award in this round
        }
}
void prepare()                  //before starting the game
{
    for(int i=0;i<5;i++)        //set the starting values
    {
        movetime[i]=-1;
        site[i]=-1;
        money[i]=2;
    }
    for(int i=0;i<15;i++)       //draw the coordinates
    {
        list1[5][i]=1+i;
    }
    counter=0;                  //reset the number of dice that is thrown
    while(counter<5)            //throw the dice 5 times
    {
        color=rand()%5;         //choose the color
        if(movetime[color]==round)  //color is used
        {
            continue;
        }
        movetime[color]++;
        counter++;
        step[color]=rand()%3+1;     //choose the number of steps
        site[color]=site[color]+step[color];    //set the new site
        for(int i=4;i>=0;i--)
        {
            if(list1[i][site[color]]!=0)        //wrong site
            {
                continue;
            }
            else
            {
                list1[i][site[color]]=16+color;     //right site
            }
            print();                            //print
            system("pause");
            break;
        }
    }
    round++;                                    //enter round1
    counter=0;                                  //reset the number of dice be thrown
    for(int i=0;i<5;i++)                        //reset the camels step
    {
        step[i]=0;
    }
}
void result()
{
    int rleader=0;              //result leader
    for(int i=0;i<5;i++)
    {
        if(list1[i][16]!=0)
        {
            rleader=list1[i][16];   //find the result leader
        }
    }
    for(int i=1;i<5;i++)
    {
        if(finalchoose[i]!=0)
        {
            if(finalchoose[i]==rleader)     //guess right
            {
                money[i]=money[i]+9-finalrepeat[i]*3;
            }
            else
            {
                money[i]--;                 //guess wrong
            }
        }
    }
    print();

    int winner=0;                           // player who wins
    int maxmoney=0;                         // winner's money
    for(int i=1;i<5;i++)
    {
        if(money[i]>=maxmoney)              //find the winner's and maxmoney
        {
            winner=i;
            maxmoney=money[i];
        }
    }
    cout<<swinner<<winner;                  //print out the winner
}
int main()
{
    srand(time(NULL));              //random
    prepare();                      //before game preparing
    int option=0;
    int guessoption=0;
    while(exiting==false)           //exiting=true->end
    {
       cout<<splayer<<player<<turn<<endl;   //who's turn
       cout<<action;                        //question
       cin>>option;                         //choose option
       if(option==1)                        //option1 roll the die
       {
           money[player]++;
           roll();
       }
       else if(option==2)                   //option2   guess this set
       {
           if(choose[player]!=0)            //already choose
           {
               continue;
           }
           cout<<guess;
           cin>>guessoption;                //key in your guess
           for(int i=1;i<5;i++)
           {
               if(choose[i]==15+guessoption)
               {
                    repeat[player]++;       //number of people who have guess this option
               }
           }
           choose[player]=15+guessoption;   //set the data
           print();
       }
       else if(option==3)                   //option 3 guess the whole game
       {
           if(finalchoose[player]!=0)       //already choose
           {
               continue;
           }
           cout<<guess;
           cin>>guessoption;                //key in the guess
           for(int i=1;i<5;i++)
           {
               if(finalchoose[i]==15+guessoption)
               {
                    finalrepeat[player]++;          //number of people who have guess this option
               }
           }
           finalchoose[player]=15+guessoption;      //set the data
           print();
       }
       player++;                                    //turn next player
       if(player==5)                                //player4 to player1
       {
           player=1;
       }
    }
    result();                                       //find the result
    return 0;
}
package ce1002.project.s103502522;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

public class P extends JFrame implements ActionListener, MouseListener {

	public P() {
		
	}

	public static void main(String[] args) {
		new P();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub

	}
}
