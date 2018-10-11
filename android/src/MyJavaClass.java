//package com.kdab.training;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;
import java.util.ArrayList;
import java.util.List;

public class MyJavaClass
{
    private int size = 0;
    private ArrayAdapter adapter;
    private List<ScanResult> results;
    private ArrayList<String> arrayList = new ArrayList<String>();

    // this method will be called from C/C++

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

    private static ArrayList<String> scanWifi(Context context) {
        WifiManager wifiManager = (WifiManager) context.getSystemService(context.WIFI_SERVICE);
        wifiManager.startScan();
        List<ScanResult> results = wifiManager.getScanResults();
        ArrayList<String> ssids = new ArrayList<String>();
        for (ScanResult scanResult : results) {
            ssids.add(scanResult.SSID);
        }
        return ssids;
    }
}
