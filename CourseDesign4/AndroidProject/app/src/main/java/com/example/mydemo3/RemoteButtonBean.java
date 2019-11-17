package com.example.mydemo3;

/**
 * Created by Administrator on 2018/7/18.
 */

public class RemoteButtonBean {
    public int id;
    public String keyName;
    public int flag;

    public int getLearnFlag() {
        return learnFlag;
    }

    public void setLearnFlag(int learnFlag) {
        this.learnFlag = learnFlag;
    }

    private int learnFlag;

    public RemoteButtonBean() {
    }

    public RemoteButtonBean(int id, String keyName, int flag, int learnFlag) {
        this.id = id;
        this.keyName = keyName;
        this.flag = flag;
        this.learnFlag = learnFlag;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getKeyName() {
        return keyName;
    }

    public void setKeyName(String keyName) {
        this.keyName = keyName;
    }

    public int getFlag() {
        return flag;
    }

    public void setFlag(int flag) {
        this.flag = flag;
    }
}
