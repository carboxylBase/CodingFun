import java.util.Scanner;

public class HZYAvg {
    public static void main(String[] args){
        int n,m;
        Scanner scanner = new Scanner(System.in);

        String s;
        s = scanner.nextLine();
        n = Integer.parseInt(s);
        m = n;

        double sum = 0;
        for (int i = 1;i<n+1;i++){
            s = scanner.nextLine();

            try {
                int number = Integer.parseInt(s);
                sum += number;
            } catch (NumberFormatException e) {
                System.out.println("输入的不是一个整数!");
                m--;
            }
        }

        System.out.println(sum / m);
        return;
    }
}
