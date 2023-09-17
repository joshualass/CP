import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.math.BigInteger;

public class MaximalAND {
    public static void main(String[] args) throws IOException
    {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line = in.readLine();
        int counter = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line.charAt(i) == '?')
            {
                counter++;
            }
        }

        BigDecimal total = new BigDecimal("0");
        BigDecimal ones = new BigDecimal("0");

        for (int i = 0; i < line.length(); i++)
        {
            switch (line.charAt(i))
            {
                case '0':
                    total = total.add(ones);
                    break;
                case '1':
                    ones = ones.add(new BigDecimal("1"));
                    break;
                case '?':
                    total = total.add(ones.divide(new BigDecimal("2")));
                    ones = ones.add(new BigDecimal("0.5"));
                    break;

            }

        }
//      System.out.println(total);
        while (total.remainder(BigDecimal.ONE).compareTo(BigDecimal.ZERO) != 0)
        {
            total = total.multiply(new BigDecimal("2"));
            counter--;
        }
        BigInteger totalI = total.toBigInteger();
        while (counter > 0)
        {
            counter--;
            totalI = totalI.multiply(new BigInteger("2"));
            totalI = totalI.mod(new BigInteger("1000000007"));
        }
        totalI = totalI.mod(new BigInteger("1000000007"));
        System.out.println(totalI);

    }
}