import java.util.Scanner;

public class HZYString {
    public static void main(String[] args) {
        System.out.println("请输入一段字符串 : ");
        Scanner scanner = new Scanner(System.in);

        String S = scanner.nextLine();
        System.out.println("字符数 : " + S.length());

        int cnt = 0;
        for (int i = 0;i<S.length();i++){
            char c = S.charAt(i);
            if (c >= 'A' && c <= 'Z'){
                cnt++;
            }
        }
        System.out.println("单词数 : " + cnt);

        System.out.print("反转字符串是 : ");
        for (int i = S.length() - 1;i>=0;i--){
            char c = S.charAt(i);
            System.out.print(c);
        }
        System.out.println();

        System.out.print("转换为大写 : ");
        for (int i = 0;i<S.length();i++){
            char c = S.charAt(i);
            if (c >= 'a'){
                c -= 'a' - 'A';
            }
            System.out.print(c);
        }

        return;
    }    
}
