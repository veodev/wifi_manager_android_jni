import android.content.Context;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiConfiguration;
import java.util.ArrayList;
import java.util.List;

public class JniClass
{               
    public static boolean enableWifi(Context context)
    {
        WifiManager wifiManager = (WifiManager) context.getSystemService(context.WIFI_SERVICE);
        return wifiManager.setWifiEnabled(true);
    }

    public static boolean disableWifi(Context context)
    {
        WifiManager wifiManager = (WifiManager) context.getSystemService(context.WIFI_SERVICE);
        return wifiManager.setWifiEnabled(false);
    }

    public static boolean isWifiEnabled(Context context)
    {
        WifiManager wifiManager = (WifiManager) context.getSystemService(context.WIFI_SERVICE);
        return wifiManager.isWifiEnabled();
    }

    private static String scanWifi(Context context) {
        WifiManager wifiManager = (WifiManager) context.getSystemService(context.WIFI_SERVICE);
        wifiManager.startScan();
        ArrayList<String> networkSsids = new ArrayList<String>();
        String result = new String();
        for (ScanResult scanResult : wifiManager.getScanResults()) {
            networkSsids.add(scanResult.SSID);

        }
        for (String item : networkSsids) {
            result = result.concat(item).concat("///");
            System.out.println(item);
        }
        System.out.println(result);
        return result;
    }

    private static void connectToSsid(Context context, String ssid) {        
        System.out.println(ssid);
        WifiConfiguration wifiConfig = new WifiConfiguration();
        wifiConfig.SSID = String.format("\"%s\"", ssid);
        wifiConfig.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.NONE);
        WifiManager wifiManager = (WifiManager) context.getSystemService(context.WIFI_SERVICE);
        int netId = wifiManager.addNetwork(wifiConfig);
        System.out.println("============ ID:");
        System.out.println(netId);
        List<WifiConfiguration> listConfigs = wifiManager.getConfiguredNetworks();

        for (WifiConfiguration conf: listConfigs) {
            if (conf.SSID != null && conf.SSID.equals("\"" + ssid + "\"")) {
                wifiManager.disconnect();
                wifiManager.enableNetwork(netId, true);
                wifiManager.reconnect();
                break;
            }
        }

    }
}
