package com.example.mydemo3;

import java.util.HashMap;

public class ConstantValues_bk {
    public static final HashMap<String,String> codeMaps = new HashMap<String, String>();
    public  static String SP_USERNAME = "userName";
    public  static String SP_USERPWD = "userPwd";
    public  static final String SP_FILENAME = "";

    static {
        codeMaps.put("00000","处理成功");
        codeMaps.put("10001","TOKEN不存在或长度不足");
        codeMaps.put("00001","数据库操作失败");
        codeMaps.put("10002","TOKEN已失效");
        codeMaps.put("10003","TOKEN中的SN号不正");
        codeMaps.put("10004","签名不存在");
        codeMaps.put("10005","时间戳不存在");
        codeMaps.put("10006","签名不正确");
        codeMaps.put("20001","用户名或密码不存在");
        codeMaps.put("20002","用户不存在或已暂停使用");
        codeMaps.put("20003","登录失败次数过多");
        codeMaps.put("20004","用户名或密码不正确");
        codeMaps.put("20005","本地用户权限不足");
        codeMaps.put("20101","服务器端URL或酒店名或房间号或APIKEY不存在");
        codeMaps.put("20201","红外KEY不存在");
        codeMaps.put("20202","红外码值不存在");
        codeMaps.put("20203","红外设备不存在");
        codeMaps.put("20204","红外码库导入失败");
        codeMaps.put("20205","红外发射失败");
        codeMaps.put("20206","红外设备已离线");
        codeMaps.put("20301","参数不正_CMD0不存在");
        codeMaps.put("20000","请求超时");

    }
}
