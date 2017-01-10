<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Prepare a simple form to add an entry, with all the textfielderesting fields.
 */
function calcmet_form_addtubebezshva($form, &$form_state) {
  $form = array();
  
  $form['addtubeoval'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Данные по трубам'),
  );
  $form['filedown'] = array(
      '#type' => 'file',
      '#title' => 'Скачать файл',
      '#size' => 60,
  );
  $form['filesave'] = array(
      '#type' => 'submit',
      '#value' => t('Сохранить файл'),
      '#validate' => array('admin_addtubebezshva_file_validate'),
      '#submit' => array('admin_addtubebezshva_file_submit'),
  );
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Add'),
  );
  return $form;
}


function admin_addtubebezshva_file_validate($form, &$form_state){
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

function admin_addtubebezshva_file_submit($form, &$form_state){
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
        //$newarr = array();
        foreach($one_row as $entry){
            //dsm($entry);
            $entrydb = array(
            'ccid'  => 7,  
            'cucid'  => 5,  
            'tswsname'  => $entry[0].'x'.$entry[1],  
            'tswsdiametr' => $entry[0],
            'tswsthickness' => $entry[1],
            'drawonemetr' => $entry[2],
            'massonem' => $entry[3],   
          );
          //dsm($entrydb);
          $return = calcmet_entry_insert ('calcmettubessteelwithoutseam', $entrydb);
          if ($return) {
             drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entrydb, TRUE))));
           }        
        }
    } //else{
      //  calcmet_form_addpolosa_submit($form, &$form_state);
    //}    
    //drupal_set_message (t('@file закачан', array('@file' => print_r($file, TRUE))));
}