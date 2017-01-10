<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Prepare a simple form to add an entry, with all the textfielderesting fields.
 */
function calcmet_form_addsteelkrug($form, &$form_state) {
  $form = array();
  
  $form['krugdatadata'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Данные по стали круглой'),
  );
  $form['krugdatadata']['skdiametr'] = array(
    '#type'  => 'textfield',
    '#title' => t('Диаметр, мм'),
    '#size'  => 60,
  ); 
  $form['krugdatadata']['skcsa'] = array(
    '#type'  => 'textfield',
    '#title' => t('Площадь поперечного сечения, мм2'),
    '#size'  => 60,
  ); 
  $form['polosadata']['polmassonem'] = array(
    '#type'  => 'textfield',
    '#title' => t('Масса 1 м, кг'),
    '#size'  => 60,
  );
  $form['filedown'] = array(
      '#type' => 'file',
      '#title' => 'Скачать файл',
      '#size' => 60,
  );
  $form['filesave'] = array(
      '#type' => 'submit',
      '#value' => t('Сохранить файл'),
      '#validate' => array('admin_addsteelkrug_file_validate'),
      '#submit' => array('admin_addsteelkrug_file_submit'),
  );
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Add'),
  );
  return $form;
}

function calcmet_form_addsteelkrug_submit($form, &$form_state) {  
  // Save the submitted entry.
  //dsm($form_state);  
  $basename = 'calcmetsteelkrug';
  if(!empty($form_state['values']['skdiametr'] && $form_state['values']['skcsa'] && $form_state['values']['polmassonem'])){
      $entry = array(
        'ccid'  => 6,  
        'cucid'  => 2,
        'skdiametr' => $form_state['values']['skdiametr'],
        'skcsa' => $form_state['values']['skcsa'],
        'skmassonem' => $form_state['values']['skmassonem'], 
      );
  } else {
      drupal_set_message ('Введите данные');
  }   
  $return = calcmet_entry_insert ($basename, $entry);
  if ($return) {
    drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entry, TRUE))));
  }
}

function admin_addsteelkrug_file_validate($form, &$form_state){
    $validators = array(
    'file_validate_extensions' => array('jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp csv'), // Проверка на расширения
    'file_validate_size' => array(1 * 1024 * 1024), // Проверка на размер файла (максимум 1mb)
  );
  // Загружаем файл в sites/default/files (по умолчанию)
  if ($file = file_save_upload('filedown', $validators, 'private://datafiles/calcmet')) {
    $form_state['values']['filedown'] = $file; // передаём информацию о файле в ф-ю mymodule_form_submit()
  }
  else {
    form_set_error('filedown', 'Файл не был загружен');
  }
}

function admin_addsteelkrug_file_submit($form, &$form_state){
    $file = $form_state['values']['filedown'];
    if ($file){
        $file->status = FILE_STATUS_PERMANENT; // Изменяем статус файла на "Постоянный"
        file_save($file); // Сохраняем новый статус
        //drupal_set_message('Картинка загружена');
        $handle = file($file->uri);
        //dsm($handle);
        $one_row = array();
        foreach ($handle as $row){
            //dsm($row);
            $one_row[] = str_getcsv($row, ';');
        }
        //dsm($one_row[0][0]);
        $newarr = array();
        foreach($one_row as $entry){
            //dsm($entry);
            $entrydb = array(
            'ccid'  => 6,  
            'cucid'  => 2,  
            'skdiametr' => $entry[0],
            'skcsa' => $entry[1],
            'skmassonem' => $entry[2],   
          );
          //dsm($entrydb);
          $return = calcmet_entry_insert ('calcmetsteelkrug', $entrydb);
          if ($return) {
             drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entrydb, TRUE))));
           }        
        }
    } //else{
      //  calcmet_form_addpolosa_submit($form, &$form_state);
    //}    
    //drupal_set_message (t('@file закачан', array('@file' => print_r($file, TRUE))));
}