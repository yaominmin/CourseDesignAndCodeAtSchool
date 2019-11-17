package com.dhee;


import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class Memory extends JFrame implements ActionListener {
    private JMenuItem easyLevel, normalLevel, hardLevel;
    private JMenuItem commonImageIcon, hardImageIcon;
    private File easyLevelFile, normalLevelFile, hardLevelFile, gradeFile;
    private String[] imageName;
    private MemoryTestPane memoryTestPane;
    private int m = 5, n = 6;//行,列

    private Memory() {
        //设置标题
        this.setTitle("记忆测试游戏");

        //存储成绩的文件对象
        easyLevelFile = new File("初级记忆排行榜.txt");
        normalLevelFile = new File("中级记忆排行榜.txt");
        hardLevelFile = new File("高级记忆排行榜.txt");

        //bar对象，用于放置菜单
        JMenuBar bar = new JMenuBar();

        //难度级别菜单
        JMenu menuLevel = new JMenu("选择级别");
        easyLevel = new JMenuItem("初级");
        normalLevel = new JMenuItem("中级");
        hardLevel = new JMenuItem("高级");
        //把MenuItem加到Menu里面
        menuLevel.add(easyLevel);
        menuLevel.add(normalLevel);
        menuLevel.add(hardLevel);

        //排行榜菜单
        JMenu menuResult = new JMenu("查看排行榜");
        JMenuItem easyLevelResult = new JMenuItem("初级排行榜");
        JMenuItem normalLevelResult = new JMenuItem("中级排行榜");
        JMenuItem hardLevelResult = new JMenuItem("高级排行榜");
        //把MenuItem加到Menu里面
        menuResult.add(easyLevelResult);
        menuResult.add(normalLevelResult);
        menuResult.add(hardLevelResult);

        //选择图标菜单
        JMenu menuIcon = new JMenu("选择图标");
        commonImageIcon = new JMenuItem("简单图标");
        hardImageIcon = new JMenuItem("困难图标");
        //把MenuItem加到Menu里面
        menuIcon.add(commonImageIcon);
        menuIcon.add(hardImageIcon);

        //把 Menu加到bar上
        bar.add(menuLevel);
        bar.add(menuIcon);
        //bar.add(menuResult);
        setJMenuBar(bar);

        //每一个菜单项都添加监听事件
        hardImageIcon.addActionListener(this);
        commonImageIcon.addActionListener(this);
        easyLevel.addActionListener(this);
        normalLevel.addActionListener(this);
        hardLevel.addActionListener(this);
//        easyLevelResult.addActionListener(this);
//        normalLevelResult.addActionListener(this);
//        hardLevelResult.addActionListener(this);

        //创建储存排行榜的文件
        if (!easyLevelFile.exists()) {
            try {
                easyLevelFile.createNewFile();
            } catch (IOException exp) {
            }
        }
        if (!normalLevelFile.exists()) {
            try {
                normalLevelFile.createNewFile();
            } catch (IOException exp) {
            }
        }
        if (!hardLevelFile.exists()) {
            try {
                hardLevelFile.createNewFile();
            } catch (IOException exp) {
            }
        }

        memoryTestPane = new MemoryTestPane();
        int imageNum = 7;
        imageName = new String[imageNum];

        //初始化设置为低级，图片为普通图片
        for (int i = 0; i < imageName.length; i++) {
            imageName[i] = "a" + i + ".jpg";
        }
        m = 5;
        n = 6;
        gradeFile = easyLevelFile;
        memoryTestPane.initBlock(m, n, imageName, gradeFile);
        add(memoryTestPane, BorderLayout.CENTER);

        //设置界面的参数
        setBounds(100, 100, 500, 500);
        setVisible(true);
        validate();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void actionPerformed(ActionEvent event) {
        //设置等级，图片个数
        if (event.getSource() == easyLevel) {
            //设置界面的规格大小
            m = 5;
            n = 6;
            gradeFile = easyLevelFile;
            memoryTestPane.initBlock(m, n, imageName, gradeFile);
        }
        if (event.getSource() == normalLevel) {
            m = 6;
            n = 7;
            gradeFile = normalLevelFile;
            memoryTestPane.initBlock(m, n, imageName, gradeFile);
        }
        if (event.getSource() == hardLevel) {
            m = 7;
            n = 8;
            gradeFile = hardLevelFile;
            memoryTestPane.initBlock(m, n, imageName, gradeFile);
        }

        //设置图片种类
        if (event.getSource() == commonImageIcon) {
            for (int i = 0; i < imageName.length; i++) {
                imageName[i] = "a" + i + ".jpg";
            }
            memoryTestPane.setImageName(imageName);
            memoryTestPane.initBlock(m, n, imageName, gradeFile);
        }
        if (event.getSource() == hardImageIcon) {
            for (int i = 0; i < imageName.length; i++) {
                imageName[i] = "ani" + i + ".jpg";
            }
            memoryTestPane.setImageName(imageName);
            memoryTestPane.initBlock(m, n, imageName, gradeFile);
        }
    }

    public static void main(String[] args) {
        new Memory();
    }
}