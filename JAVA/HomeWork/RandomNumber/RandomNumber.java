public class RandomNumber {
    public static void main(String[] args){
        while (true){
            double x = Math.random();
            double y = Math.random();
            x = 6 * x;y = 6 * y;

            int X,Y;
            X = (int)Math.floor(x);
            Y = (int)Math.floor(y);

            X = X + 1;Y = Y + 1;
            System.out.println("骰子1: " + X + " 骰子2: " + Y + " 总点数 = " + (X + Y));

            if (X == 1 && Y == 1){
                break;
            }
        }

        return;
    }
}
