package com.dhee;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.RandomAccessFile;

public class Record extends JDialog implements ActionListener {
    private int time = 0;
    private JTextField yourName;
    private JLabel label;
    private JButton enter, cancel;
    private File gradeFile = null;

    Record() {
        setBounds(100, 100, 330, 160);
        setResizable(false);
        setModal(true);
        setVisible(false);
        enter = new JButton("确定");
        cancel = new JButton("取消");

        yourName = new JTextField(8);
        yourName.setText("匿名");

        enter.addActionListener(this);
        cancel.addActionListener(this);

        setLayout(new GridLayout(2, 1));
        label = new JLabel();
        add(label);
        JPanel p = new JPanel();
        p.add(yourName);
        p.add(enter);
        p.add(cancel);
        add(p);
    }

    void setGradeFile(File f) {
        gradeFile = f;
        setTitle("保存成绩到" + gradeFile.getName());
        label.setText("保存成绩到" + gradeFile.getName());
        validate();
    }

    void setTime(int time) {
        this.time = time;
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == enter) {
            try {
                RandomAccessFile out = new RandomAccessFile(gradeFile, "rw");
                out.seek(out.length());
                out.writeUTF(yourName.getText());
                out.writeInt(time);
                out.close();
            } catch (Exception ignored) {
            }
            setVisible(false);
        }
        if (e.getSource() == cancel) {
            setVisible(false);
        }
    }
}

