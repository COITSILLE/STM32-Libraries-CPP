#pragma once

#include "oledex_menu.h"

#define ceil_div(a, b) (((a) + (b) - 1) / (b))

template<typename OLEDType>
void OledExMenu<OLEDType>::init(){
    if (this->header == NULL){
        return;
    }
    this->focus_item = this->header;
    this->select_ptr = Pointer{0, 0};
    this->item_ref_ptr.x = this->font->height;
    this->item_ref_ptr.y = 0;
    this->frame.top_item = this->header;
    this->frame.last_focus_item = NULL;
    this->frame.rows = OLEDType::page * 8 / this->cspacing;
}

template<typename OLEDType>
void OledExMenu<OLEDType>::setFrame(){
    if (this->focus_item == NULL){
        return;
    }
    if (this->frame.last_focus_item == NULL ||
        this->focus_item == this->frame.last_focus_item->top_sub_item ||
        this->focus_item == this->frame.last_focus_item->parent_item)
    {
        this->frame.top_item = this->focus_item;
    }
    while (this->frame.top_item->prev_item != NULL){
        this->frame.top_item = this->frame.top_item->prev_item;
    }

    this->frame.cur_item = this->frame.top_item;
    int8_t roll_sign = 0;
    uint8_t rows = 0;
    if (this->focus_item != this->frame.top_item){
        while(this->frame.cur_item != NULL){
            rows += ceil_div(strlen(this->frame.cur_item->title) * this->rspacing, OLEDType::col);
            if (this->frame.cur_item == this->focus_item){
                roll_sign = 1;
                rows++;
                break;
            }
            this->frame.cur_item = this->frame.cur_item->next_item;
        }
    }
    if (roll_sign){
        if (rows > this->frame.rows){
            for (uint8_t k = 0; k < (rows - this->frame.rows); k++){
                if (this->frame.top_item->next_item != NULL)
                    this->frame.top_item = this->frame.top_item->next_item;
            }
        }
    }
    else{
        if (this->frame.top_item->prev_item != NULL)
            this->frame.top_item = this->frame.top_item->prev_item;
    }

    this->oled->clear();
    this->frame.cur_item = this->frame.top_item;
    this->frame.cur_item_ptr = this->item_ref_ptr;
    while(this->frame.cur_item_ptr.y < OLEDType::page * 8){
        if (this->frame.cur_item == NULL){
            break;
        }
        if (this->frame.cur_item == this->focus_item){
            this->select_ptr.x = 0;
            this->select_ptr.y = this->frame.cur_item_ptr.y;
        }
        this->oled->setString(this->frame.cur_item->title, &this->frame.cur_item_ptr,
            this->font, this->rspacing, this->cspacing, 0);
        this->frame.cur_item = this->frame.cur_item->next_item;
        this->frame.cur_item_ptr.x = this->item_ref_ptr.x;
        this->frame.cur_item_ptr.y += this->cspacing;
    };
    this->oled->setChar(this->pointer_char, this->select_ptr, this->font);
    this->frame.last_focus_item = this->focus_item;
}

template<typename OLEDType>
void OledExMenu<OLEDType>::goNextItem(){
    if (this->focus_item->next_item != NULL)
        this->focus_item = this->focus_item->next_item;
    this->setFrame();
    this->oled->showFrame();
}

template<typename OLEDType>
void OledExMenu<OLEDType>::goPrevItem(){
    if (this->focus_item->prev_item != NULL)
        this->focus_item = this->focus_item->prev_item;
    this->setFrame();
    this->oled->showFrame();
}

template<typename OLEDType>
void OledExMenu<OLEDType>::goNextPage(){
    if(this->focus_item->top_sub_item != NULL)
        this->focus_item = this->focus_item->top_sub_item;
    this->setFrame();
    this->oled->showFrame();
}

template<typename OLEDType>
void OledExMenu<OLEDType>::goPrevPage(){
    if(this->focus_item->parent_item != NULL)
        this->focus_item = this->focus_item->parent_item;
    this->setFrame();
    this->oled->showFrame();
}

template<typename OLEDType>
void OledExMenu<OLEDType>::enter(){
    if (this->focus_item->command != NULL){
        this->focus_item->command();
    }
}

