package com.example.mydemo3;

import java.util.HashMap;

public class ConstValues {
    private static final HashMap<String, String> codeMap = new HashMap<>();
    static final String SP_USR = "null";
    static final String SP_PWD = "null";
    static final String SP_FILE = "file";

    // Initialize the map of error code
    static{
        codeMap.put("00000", "处理成功");
        codeMap.put("00001", "数据库操作失败");
        codeMap.put("10001", "TOKEN不存在或长度不足");
        codeMap.put("10002", "TOKEN已失效");
        codeMap.put("10003", "TOKEN中的SN号不正确");
        codeMap.put("10004", "签名不存在");
        codeMap.put("10005", "时间戳不存在");
        codeMap.put("10006", "签名不正确");
        codeMap.put("20000", "请求超时");
        codeMap.put("20001", "用户名或密码不存在");
        codeMap.put("20002", "用户不存在或已暂停使用");
        codeMap.put("20003", "登录失败次数过多");
        codeMap.put("20004", "用户名或密码不正确");
        codeMap.put("20005", "本地用户权限不足");
        codeMap.put("20101", "服务器端URL或酒店名或房间号或API_KEY不存在");
        codeMap.put("20201", "红外KEY不存在");
        codeMap.put("20202", "红外码值不存在");
        codeMap.put("20203", "红外设备不存在");
        codeMap.put("20204", "红外码库导入失败");
        codeMap.put("20205", "红外发射失败");
        codeMap.put("20206", "红外设备已离线");
        codeMap.put("20301", "参数不正_CMD0不存在");
        codeMap.put("20302", "参数不正_CMD1不存在");
        codeMap.put("20303", "参数不正_PAYLOAD不存在");
        codeMap.put("20304", "窗帘设备不存在");
        codeMap.put("20305", "窗帘设备控制失败");
        codeMap.put("20306", "窗帘设备已离线");
        codeMap.put("20501", "参数不正_插座状态不存在");
        codeMap.put("20502", "插座设备不存在");
        codeMap.put("20503", "插座设备控制失败");
        codeMap.put("20504", "插座设备已离线");
        codeMap.put("20601", "参数不正_开关状态不存在");
        codeMap.put("20602", "参数不正_开关类型不存在(标识几开开关)");
        codeMap.put("20603", "开关设备不存在");
        codeMap.put("20604", "开关设备控制失败");
        codeMap.put("20605", "开关设备已掉线");
        codeMap.put("20701", "参数不正确_射灯操作类型不存在");
        codeMap.put("20702", "参数不正确_射灯操作类型不正确");
        codeMap.put("20703", "参数不正确_射灯开关状态不存在");
        codeMap.put("20704", "参数不正确_射灯色调饱和度不存在");
        codeMap.put("20705", "参数不正确_射灯亮度不存在");
        codeMap.put("20706", "射灯设备不存在");
        codeMap.put("20707", "射灯设备控制失败");
        codeMap.put("20801", "参数不正确_设备名称不存在");
        codeMap.put("20802", "端末设备不存在");
        codeMap.put("20803", "端末状态属性不存在");
        codeMap.put("20804", "参数不正确_报警时长不正确");
        codeMap.put("20805", "端末设备已离线");
        codeMap.put("20806", "设备控制失败");
    }

    // Get info by code
    static String getInfo(String code){
        String info = codeMap.get(code);
        if(info == null){
            info = "Unknow error(-1)";
        }
        else{
            info = info + "(" + code + ")";
        }
        return info;
    }
}
