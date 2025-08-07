import java.util.Date;
import java.text.SimpleDateFormat;
import java.util.TimeZone;
import java.text.DateFormat;

public class donggeon_10699 {
    public static void main(String[] args) {
        Date date = new Date();
        DateFormat df = new SimpleDateFormat("yyyy-MM-dd");
        df.setTimeZone(TimeZone.getTimeZone("Asia/Seoul"));
        System.out.println(df.format(date));
    }
}
