package com.dhee;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;

public class MemoryTestPane extends JPanel implements ActionListener, Runnable {
    private int row, col;//行，列
    private File gradeFile;
    private ArrayList<Block> allBlockList;//block数组
    private String[] imageFileName;
    private LinkedList<ImageIcon> openIconList;//添加图标对象用到的链表
    private LinkedList<Block> openBlockList;//添加方块对象用的链表
    private int success = 0;//判断是否成功变量
    private int usedTime = 0;//计时
    private JTextField showUsedTime, hintMessage;//已用时间，提示信息，
    private Timer timer;//计时器对象
    private Record record;//成绩记录
    private JPanel centerPanel;//中间面板，放置block

    MemoryTestPane() {
        setLayout(new BorderLayout());
        //初始化
        allBlockList = new ArrayList<>();
        openIconList = new LinkedList<>();
        openBlockList = new LinkedList<>();
        record = new Record();
        centerPanel = new JPanel();
        JPanel southPanel = new JPanel();

        //显示提示信息
        hintMessage = new JTextField();
        hintMessage.setHorizontalAlignment(JTextField.CENTER);
        hintMessage.setEditable(false);
        hintMessage.setFont(new Font("宋体", Font.BOLD, 18));

        //显示已用时间
        showUsedTime = new JTextField(8);
        showUsedTime.setEditable(false);
        showUsedTime.setHorizontalAlignment(JTextField.CENTER);
        //添加到面板
        southPanel.add(new JLabel("用时:"));
        southPanel.add(showUsedTime);
        add(southPanel, BorderLayout.SOUTH);
        add(hintMessage, BorderLayout.NORTH);
        //设置计时器
        timer = new Timer(1000, this);

    }

    //将block设置初始化
    void initBlock(int m, int n, String[] name, File f) {
        //设置行，列。初始化
        row = m;
        col = n;
        gradeFile = f;
        centerPanel.removeAll();
        imageFileName = name;
        ImageIcon[] icon = new ImageIcon[imageFileName.length];
        //初始化icon数组
        for (int i = 0; i < icon.length; i++) {
            icon[i] = new ImageIcon(imageFileName[i]);
        }

        //初始化block数组
        if (allBlockList.isEmpty()) {
            for (int i = 0; i < row * col; i++) {
                allBlockList.add(new Block());
            }
        } else {
            allBlockList.clear();
            for (int i = 0; i < row * col; i++) {
                allBlockList.add(new Block());
            }
        }

        //为每一个block添加监听
        for (int i = 0; i < allBlockList.size(); i++) {
            allBlockList.get(i).addActionListener(this);
            allBlockList.get(i).setOpenedIcon(icon[i % row]);
        }
        //随机打乱
        Collections.shuffle(allBlockList);
        //设置grid布局
        centerPanel.setLayout(new GridLayout(row, col));
        //将block加到面板上
        for (Block block : allBlockList) {
            centerPanel.add(block);
        }
        //将面板放到中间
        add(centerPanel, BorderLayout.CENTER);
        //停止计时器
        if (timer.isRunning()) {
            timer.stop();
        }
        //设置提示信息的内容
        hintMessage.setText("您需要用鼠标连续单击出" + col + "个同样图标的方块");
        usedTime = 0;
        showUsedTime.setText(null);
        validate();
    }

    //设置图片的名称
    void setImageName(String[] name) {
        imageFileName = name;
    }

    //响应函数
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() instanceof Block) {
            if (!timer.isRunning())
                timer.start();
            Block block = (Block) e.getSource();
            ImageIcon openStateIcon = block.getOpenedIcon();
            block.setIcon(openStateIcon);
            if (openIconList.size() == 0) {
                openIconList.add(openStateIcon);
                openBlockList.add(block);
                success = 1;
            } else {
                ImageIcon temp = openIconList.getLast();
                if (temp == openStateIcon && !(openBlockList.contains(block))) {
                    success = success + 1;
                    openIconList.add(openStateIcon);
                    openBlockList.add(block);
                    if (success == col) {
                        for (Block value : allBlockList) {
                            value.setEnabled(false);
                        }
                        for (Block b : openBlockList) {
                            b.setDisabledIcon(b.getOpenedIcon());
                        }
                        timer.stop();
                        record.setTime(usedTime);
                        record.setGradeFile(gradeFile);
                        record.setVisible(true);
                    }
                } else if ((temp != openStateIcon) && (!(openBlockList.contains(block)))) {
                    openIconList.clear();
                    openBlockList.clear();
                    openIconList.add(openStateIcon);
                    openBlockList.add(block);
                    success = 1;
                    for (Block value : allBlockList) {
                        if (value != block)
                            value.setIcon(null);
                    }
                }
            }
        }
        if (e.getSource() == timer) {
            usedTime++;
            showUsedTime.setText("您的用时:" + usedTime + "秒");
        }
    }

    //多线程
    public void run() {
        for (Block block : allBlockList) block.setIcon(block.getOpenedIcon());
        try {
            Thread.sleep(1000);
        } catch (InterruptedException ignored) {
        }
        for (Block block : allBlockList) block.addActionListener(this);
        for (Block block : allBlockList)
            if (!openBlockList.contains(block))
                block.setIcon(null);
    }
}