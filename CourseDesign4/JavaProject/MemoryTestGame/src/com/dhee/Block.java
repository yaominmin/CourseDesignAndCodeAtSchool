package com.dhee;

import javax.swing.*;

class Block extends JButton {
    private ImageIcon openedIcon;//翻开时的图标

    //取得翻开的图标
    ImageIcon getOpenedIcon() {
        return openedIcon;
    }

    //设置翻开的图标
    void setOpenedIcon(ImageIcon icon) {
        openedIcon = icon;
    }
}