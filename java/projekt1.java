//Adam Kolakowski. Zadanie 5

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.ArrayList;
import java.util.List;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class plansza extends JFrame {
int tabstale[][] = new int[10][10];
JButton tab[][] = new JButton[10][10] ;
JFrame ramka = new JFrame("Pomoc");
JPanel szachownica = new JPanel();
JPanel menu = new JPanel();
JTextField t = new JTextField(10);
ImageIcon X = new ImageIcon("X.png");
ImageIcon O = new ImageIcon("O.png");
JRadioButton xButton = new JRadioButton("CZARNE");
JRadioButton oButton = new JRadioButton("BIALE");
List<String> stan = new ArrayList<String>();
JButton zapis =  new JButton("zapis");
JTextField tzapis = new JTextField(20);
JButton cofnij = new JButton("cofnij");
JButton wczytaj =  new JButton("wczytaj");
JButton help =  new JButton("pomoc");
JButton Sprawdz =  new JButton("Sprawdz");
JTextField twczytaj = new JTextField(20);
String TekstHelp = "<html>Pusre pola diagramu 10x10 nalezy zapelnic bialymi i czarnymi krazkami tak, aby<br> - wszystklie biale krazki stanowily zwarta grupe i wszystkie czarne rowniez (zwarta grupe tworza krazki lezace na polach stanowiacych razem jeden wielokat<br> zadnego czteropolowego kwadratu nie zjamowaly krazki tego samego koloru<br> <br>STEROWANIE:<br>Po prawej wybiera sie rodzaj krazka. Aby usunac postawiony wczesniej krazek, nalezy wybrac ten sam jego rodzaj i kliknac na planszy.<br>Krazkow stalych nie da sie modyfikowac";

JLabel tekstNaHelpie = new JLabel(TekstHelp, SwingConstants.CENTER);




    public plansza() {

ramka.setVisible(false);
ramka.setSize(900,500);
ramka.add(tekstNaHelpie);
//RadioButtons group
 ButtonGroup group = new ButtonGroup();
 group.add(xButton);
 group.add(oButton);
 xButton.setSelected(true);

        //Organizacja okienka
        Container cp = getContentPane();
        cp.setLayout(new GridLayout(1,2));
        cp.add(szachownica);
        cp.add(menu);

        //Organizacja szachownicy
        szachownica.setLayout(new GridLayout(10,10));
        for (int i=0; i<10; i++)
            for(int j=0; j<10; j++)
            {
		
                tab[i][j]=new JButton("");
                szachownica.add(tab[i][j]);
                (tab[i][j]).addActionListener(new Click(i,j));
		tab[i][j].setBackground(new Color(255,251,214));
            }
        ustawPocz();
        //Organizacja menu
        menu.setLayout(new GridLayout(5,2));
        //menu.add(t);
        menu.add(xButton);
        menu.add(oButton);
        menu.add(zapis);
        menu.add(tzapis);
        menu.add(wczytaj);
        menu.add(twczytaj);
        menu.add(cofnij);
        zapis.addActionListener(new ClickZapis());
        menu.add(help);
        menu.add(Sprawdz);
        Sprawdz.addActionListener(new ClickSprawdz());
        cofnij.addActionListener(new ClickCofnij());
        wczytaj.addActionListener(new ClickWczytaj());
        help.addActionListener(new Clickhelp());
        //Opis okienka
        setTitle("Gra");
        setVisible(true);
        setSize(600,400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

    }


    class Click implements ActionListener {

    int a, b;
    Click(int a, int b) {
        this.a=a; this.b=b;
    }

    public void actionPerformed(ActionEvent e)
    {
        //t.setText(tab[a][b].getIcon());

        if((tab[a][b]).getIcon()==null)
        {
            if (xButton.isSelected())
            {
                (tab[a][b]).setIcon(X);
                stan.add("dx"+a+b);
            }
            else
            {
                (tab[a][b]).setIcon(O);
                stan.add("do"+a+b);
            }
        }
        else
        {
            if ((tabstale[a][b]) != 1){
            if (((tab[a][b]).getIcon()==X) && (xButton.isSelected()==true)) {(tab[a][b]).setIcon(null); stan.add("ux"+a+b); }
            if (((tab[a][b]).getIcon()==O) && (oButton.isSelected()==true)) {(tab[a][b]).setIcon(null); stan.add("uo"+a+b); }}
        }
    }
    }
    class ClickZapis implements ActionListener {

      public void actionPerformed(ActionEvent e) {
 
        try
        {
        save();
        }
        catch (FileNotFoundException ex)
        {
        System.out.println(".");
      }
    }
    }

    class ClickCofnij implements ActionListener {

      public void actionPerformed(ActionEvent e) {
          if (!(stan.isEmpty())){
        readCom(stan.get((stan.size())-1));
          }
      }
    }

    class Clickhelp implements ActionListener {

      public void actionPerformed(ActionEvent e) {
          ramka.setVisible(true);
          }
      }

       class ClickSprawdz implements ActionListener {

      public void actionPerformed(ActionEvent e) {
          if (Sprawdz()==true) Sprawdz.setText("Dobrze");
	else Sprawdz.setText("Zle");
          }
      }

    class ClickWczytaj implements ActionListener {

      public void actionPerformed(ActionEvent e) {
          String linia;
            FileReader plik=null;
            int x;
            int y;
            char operacja;
            char przycisk;
          try
          {
            plik = new FileReader(twczytaj.getText());
          }
           catch (FileNotFoundException ne)
          {
                      System.out.println("BLAD");
          }

          BufferedReader bplik = new BufferedReader(plik);
          try
          {
            //czyszczenie planszy
            for (int i=0; i<10; i++)
                for (int j=0; j<10; j++)

                (tab[i][j]).setIcon(null);

        ustawPocz();
        stan.clear();
          while ((linia = bplik.readLine())!=null){
            operacja=linia.charAt(0);
            x=(int)linia.charAt(2)-'0';
        y=(int)linia.charAt(3)-'0';
        przycisk=linia.charAt(1);
        stan.add(linia);
        if (operacja=='d'){
            if (przycisk=='x')
            (tab[x][y]).setIcon(X);
            if (przycisk=='o')
             (tab[x][y]).setIcon(O);
        }
        if (operacja=='u') (tab[x][y]).setIcon(null);

          }


          }
          catch (IOException es)
          {
              System.out.println("dsdd");
          }

      }
    }



        public void readCom (String com) {
        int x;
        int y;
        char przycisk;
        char operacja;

        operacja=com.charAt(0);
        przycisk=com.charAt(1);
        x=(int)com.charAt(2)-'0';
        y=(int)com.charAt(3)-'0';


        if (operacja=='d'){
        (tab[x][y]).setIcon(null); stan.remove((stan.size())-1);}
        else if (operacja=='u'){
                if (przycisk=='x')
                    {(tab[x][y]).setIcon(X); stan.remove((stan.size())-1);}
                if (przycisk=='o')
                    {(tab[x][y]).setIcon(O); stan.remove((stan.size())-1);}
        }
    }


    public void save() throws FileNotFoundException{
        try
        {

        PrintWriter plik = new PrintWriter(tzapis.getText());

        for (int i=0; i<stan.size(); i++)
        {
            plik.println(stan.get(i));
        }
        plik.close();
        }

        catch (FileNotFoundException ex)
        {
            System.out.println(ex);
        }
  }

  public void ustawPocz()
  {

      (tab[1][2]).setIcon(X); tabstale[1][2]=1;  //X = BIALE
      (tab[1][6]).setIcon(X); tabstale[1][6]=1;
      (tab[2][4]).setIcon(X); tabstale[2][4]=1;
      (tab[3][2]).setIcon(O); tabstale[3][2]=1;
      (tab[3][3]).setIcon(O); tabstale[3][3]=1;
      (tab[3][4]).setIcon(O); tabstale[3][4]=1;
      (tab[3][6]).setIcon(X); tabstale[3][6]=1;
      (tab[3][8]).setIcon(O); tabstale[3][8]=1;
      (tab[3][9]).setIcon(O); tabstale[3][9]=1;
      (tab[4][0]).setIcon(O); tabstale[4][0]=1;
      (tab[4][1]).setIcon(O); tabstale[4][1]=1;
      (tab[4][6]).setIcon(O); tabstale[4][6]=1;
      (tab[5][2]).setIcon(X); tabstale[5][2]=1;
      (tab[5][4]).setIcon(O); tabstale[5][4]=1;
      (tab[5][6]).setIcon(X); tabstale[5][6]=1;
      (tab[5][8]).setIcon(X); tabstale[5][8]=1;
      (tab[6][0]).setIcon(X); tabstale[6][0]=1;
      (tab[6][3]).setIcon(X); tabstale[6][3]=1;
      (tab[6][7]).setIcon(X); tabstale[6][7]=1;
      (tab[7][1]).setIcon(X); tabstale[7][1]=1;
      (tab[7][2]).setIcon(X); tabstale[7][2]=1;
      (tab[7][5]).setIcon(O); tabstale[7][5]=1;
      (tab[7][7]).setIcon(X); tabstale[7][7]=1;
      (tab[8][9]).setIcon(X); tabstale[8][9]=1;
      (tab[8][6]).setIcon(X); tabstale[8][6]=1;
  }

public boolean Sprawdz()
{

    for (int i=0; i<9; i++)
    for (int j=0; j<9; j++){
    int czarne=0;
    int biale=0;

    if ((tab[i][j]).getIcon()==X) biale++;
    if ((tab[i][j]).getIcon()==O) czarne++;

    if ((tab[i+1][j]).getIcon()==X) biale++;
    if ((tab[i+1][j]).getIcon()==O) czarne++;

    if ((tab[i][j+1]).getIcon()==X) biale++;
     if ((tab[i][j+1]).getIcon()==O) czarne++;

    if ((tab[i+1][j+1]).getIcon()==X) biale++;
    if ((tab[i+1][j+1]).getIcon()==O) czarne++;

    if (czarne>3 || biale>3) return false;
    }

    for (int i=0; i<9; i++)
    for (int j=0; j<9; j++){
    if ((tab[i][j]).getIcon()!=null){
    if (i<9 && j<9 && i>0 && j>0)
    {
        int jest=0;
        if ((tab[i-1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i+1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j-1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j+1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if (jest==0) return false;
    }

    if (i==0 && j==0)
    {
            int jest=0;
        if ((tab[i+1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j+1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if (jest==0) return false;
    }

    if (i==9 && j==9)
    {
            int jest=0;
        if ((tab[i-1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j-1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if (jest==0) return false;
    }


    if (i==9 && j==0)
    {
            int jest=0;
        if ((tab[i-1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j+1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if (jest==0) return false;
    }

    if (i==0 && j==9)
    {
            int jest=0;
        if ((tab[i+1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j-1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if (jest==0) return false;
    }

    if (i==0 && j>0 && j<9)
        {
            int jest=0;
        if ((tab[i+1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j+1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j-1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if (jest==0) return false;
    }

    if (i==9 && j>0 && j<9)
        {
            int jest=0;
        if ((tab[i-1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j+1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j-1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if (jest==0) return false;
    }

    if (i>0 && i<9 && j==0)
        {
            int jest=0;
        if ((tab[i+1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j+1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i-1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if (jest==0) return false;
    }

    if (i>0 && i<9 && j==9)
        {
            int jest=0;
        if ((tab[i+1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i][j-1]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if ((tab[i-1][j]).getIcon()==(tab[i][j]).getIcon()) jest++;
        if (jest==0) return false;
    }

    }
    }

    return true;


}



public static void main(String[] args)
{

    JFrame ramka = new plansza();

}
}

