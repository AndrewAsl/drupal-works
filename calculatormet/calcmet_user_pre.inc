<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function calcmet_customer_form($form, &$form_state){
    $form = array();
    
    $options1 = array(
        2 => t('Арматура'),
        3 => t('Двутавр'),
        4 => t('Квадрат'),
        5 => t('Полоса'),
        6 => t('Сталь'),
        7 => t('Труба'),
        8 => t('Швеллер'),
        9 => t('Шестигранник'),
        10 => t('Круглый прокат'),
    );
    $selectcat = isset($form_state['values']['category'])? ($form_state['values']['category']) : key($options1);
    
    $form['choisecategory'] = array(
        '#type'  => 'fieldset',
        '#title' => t('Выберите тип металлопроката'),
    );
    $form['choisecategory']['category'] = array(
        '#type'  => 'select',
        '#options' => $options1,
        '#size' => 9,
        '#default_value' => $selectcat,
        '#ajax' => array(
            'callback' => 'calcmet_get_undercategory',
            'wrapper' => 'undercategory',
        ),
    );    
    $form['choisecategory']['undercategory'] = array(
        '#title' => t('Выберите подкатегорию'),
        '#type' => 'select',
        '#options' => calcmet_get_undercatoptions($selectcat),
        '#prefix' => '<div id="undercategory">',
        '#suffix' => '</div>',        
    );
    $form['choisecategory']['picture'] = array(
        '#title' => t('Чертеж'),
        '#type' => '',
        '#options' => calcmet_get_undercatoptions($selectcat),
        '#prefix' => '<div id="undercategory">',
        '#suffix' => '</div>',        
    );
    
    $form_state['ccid'] = isset($form_state['values']['category'])? ($form_state['values']['category']):2;
    $form_state['cucid'] = isset($form_state['values']['undercategory'])? ($form_state['values']['undercategory']):0;
    
    
    $form['tabledbname'] = array(
        '#title' => t('Имя таблицы базы данных'),
        '#type' => 'hidden',
        //'#default_value' => 'calcmetarmatura',
        '#value' => calcmet_get_tableDB_name($form_state['ccid'], $form_state['cucid']),//$tablename,                
    );
    
    $form['calczone'] = array(
        '#title' => t('Рассчитать'),
        '#type' => 'fieldset',
    );
    $form['calczone']['prokatname'] = array(
        '#title' => 'Выберите название',
        '#type' => 'textfield',
        '#size' => 60,
        //'#autocomplete_path' => 'services/calcmet/calcmet_autokomplit_prokatname_callback',
    );
    $form['calczone']['prokatlength'] = array(
        '#title' => 'Введите длину в метрах',
        '#type' => 'textfield',
        '#size' => 60,
        //'#autocomplete_path' => 'services/calcmet/calcmet_autokomplit_prokatname_callback',
    );
    $form['calczone']['prokatlength'] = array(
        '#title' => 'Введите длину в метрах',
        '#type' => 'textfield',
        '#size' => 60,
        //'#autocomplete_path' => 'services/calcmet/calcmet_autokomplit_prokatname_callback',
    );
    $form['calczone']['submit'] = array(
        '#value' => 'Произвести расчет',
        '#type' => 'submit',
        '#validate' => array('calcmet_userinput_validate'),
        '#submit' => array('calcmet_userinput_submit'),
    );
    $form['calcitog'] = array(
        '#title' => t('Результаты расчета'),
        '#type' => 'fieldset',
    );
    
    
    return $form;
}

/*
function calcmet_get_undercategory($form, $form_state){
    if ( !empty ($form['undercategory']['#options'])){
        //$commands[] = ajax_command_remove("#undercategory");
        $commands[] = ajax_command_insert("#undercategory",          
          drupal_render($form['undercategory']));
        //return $form['undercategory'];
    } else {
        $commands[] = ajax_command_replace("#undercategory", 
          "<div id='undercategory'>".
          drupal_render($form['calczone']).
          "</div>" );
    }
    return array('#type' => 'ajax', '#commands' => $commands);
}
 * 
 */
function calcmet_get_undercategory($form, $form_state){
    return $form['undercategory'];
}

function calcmet_get_undercatoptions($key){
    $entries = db_select('calcmetundercat', 'uc')
            -> fields('uc')
            -> condition ('uc.ccid', $key)
            -> execute()
            -> fetchAll();
    //dsm($entries);
    foreach ($entries as $entry) {
      $options[$entry->cucid] = $entry->title;
    }
    if (isset($options)) {
        return $options;
    }
    else {
        return array('В данной категории подразделы отсуствуют');
    }
}

function calcmet_get_tableDB_name($form, $form_state){
    $schemas = drupal_get_schema();
    $tableDBnames = array();
    foreach ($schemas as $schema){
        if ($schema['module'] == 'calcmet'){
            $tableDBnames[] = $schema['name'];
        }    
    }
    //dsm($tableDBnames);
    $ccid = $form_state['ccid'];
    $cucid = $form_state['cucid'];
    unset ($tableDBnames[0], $tableDBnames[1], $tableDBnames[2]);
    /*foreach ($tableDBnames as $tableDBname){
        $record = db_select($tableDBname)
                ->fields($tableDBname, array('ccid', 'cucid'))
                ->condition('ccid', $ccid)
                ->condition('cucid', $cucid)
                ->countQuery()
                ->execute()
                ->fetchField();
    }
    //dsm($record);*/
}