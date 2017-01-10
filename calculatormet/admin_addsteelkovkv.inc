<?php
/**
 * Prepare a simple form to add an entry, with all the textfielderesting fields.
 */
function calcmet_form_addsteelkovkv($form, &$form_state) {
  $form = array();  
  $form['kovkvdata'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Данные по стали круглой'),
  );
  $form['kovkvdata']['skkvstorona'] = array(
    '#type'  => 'textfield',
    '#title' => t('Диаметр, мм'),
    '#size'  => 60,
  ); 
  $form['kovkvdata']['skkvcsa'] = array(
    '#type'  => 'textfield',
    '#title' => t('Площадь поперечного сечения, мм2'),
    '#size'  => 60,
  ); 
  $form['kovkvdata']['skkvmassonem'] = array(
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
      '#validate' => array('admin_addsteelkovkv_file_validate'),
      '#submit' => array('admin_addsteelkovkv_file_submit'),
  );
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Add'),
  );
  return $form;
}

function calcmet_form_addsteelkovkv_submit($form, &$form_state) {  
  $basename = 'calcmetsteelkovkvadrat';
  if(!empty($form_state['values']['skkvstorona'] && $form_state['values']['skkvcsa'] && $form_state['values']['skkmassonem'])){
      $entry = array(
        'ccid'  => 6,  
        'cucid'  => 4,
        'skkvstorona' => $form_state['values']['skkvstorona'],
        'skkvcsa' => $form_state['values']['skkvcsa'],
        'skkvmassonem' => $form_state['values']['skkmassonem'], 
      );
  } else {
      drupal_set_message ('Введите данные');
  }   
  $return = calcmet_entry_insert ($basename, $entry);
  if ($return) {
    drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entry, TRUE))));
  }
}

function admin_addsteelkovkv_file_validate($form, &$form_state){
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

function admin_addsteelkovkv_file_submit($form, &$form_state){
    $file = $form_state['values']['filedown'];
    if ($file){
        $file->status = FILE_STATUS_PERMANENT; // Изменяем статус файла на "Постоянный"
        file_save($file); // Сохраняем новый статус
        $handle = file($file->uri);
        $one_row = array();
        foreach ($handle as $row){
            $one_row[] = str_getcsv($row, ';');
        }
        foreach($one_row as $entry){
            $entrydb = array(
            'ccid'  => 6,  
            'cucid'  => 4,  
            'skkvstorona' => $entry[0],
            'skkvcsa' => $entry[1],
            'skkvmassonem' => $entry[2],   
          );
          $return = calcmet_entry_insert ('calcmetsteelkovkvadrat', $entrydb);
          if ($return) {
             drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entrydb, TRUE))));
           }        
        }
    } 
}