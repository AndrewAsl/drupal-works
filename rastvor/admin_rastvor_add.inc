<?php

function rastvor_form_add($form, &$form_state) {
  $form['rastvorcat']['filedown'] = array(
      '#type' => 'file',
      '#title' => 'Скачать файл',
      '#size' => 60,
  );
  $form['rastvorcat']['filesave'] = array(
      '#type' => 'submit',
      '#value' => t('Сохранить файл'),
      '#validate' => array('admin_cat_file_validate'),
      '#submit' => array('admin_cat_file_submit'),
  );
  /*$form['rastvortype']['filedown'] = array(
      '#type' => 'file',
      '#title' => 'Скачать файл',
      '#size' => 60,
  );
  $form['rastvortype']['filesave'] = array(
      '#type' => 'submit',
      '#value' => t('Сохранить файл'),
      '#validate' => array('admin_addtube1_file_validate'),
      '#submit' => array('admin_addtube1_file_submit'),
  );
  $form['rastvorcement']['filedown'] = array(
      '#type' => 'file',
      '#title' => 'Скачать файл',
      '#size' => 60,
  );
  $form['rastvorcement']['filesave'] = array(
      '#type' => 'submit',
      '#value' => t('Сохранить файл'),
      '#validate' => array('admin_addtube1_file_validate'),
      '#submit' => array('admin_addtube1_file_submit'),
  );
  $form['rastvordataset']['filedown'] = array(
      '#type' => 'file',
      '#title' => 'Скачать файл',
      '#size' => 60,
  );
  $form['rastvordataset']['filesave'] = array(
      '#type' => 'submit',
      '#value' => t('Сохранить файл'),
      '#validate' => array('admin_addtube1_file_validate'),
      '#submit' => array('admin_addtube1_file_submit'),
  );*/
  $form['tbl'] = array(
      '#type' => 'item',
      '#markup' => 
//      '<div><table class="table-bordered"><tbody>'
//      . '<tr>'
//      . '<th>Вид раствора</th>'
//      . '<th>Марка (состав) раствора</th>'
//      . '<th>Марка цемента</th>'
//      . '<th>Расход цемента, т </th>'
//      . '<th>Расход песка, м3 </th>'
//      . '<th>Расход извести, т </th>'
//      . '<th>Расход воды, м3 </th>'
//      . '</tr>'
      rastvor_all_union_table(),
  );
  return $form;
}
function admin_cat_file_validate($form, &$form_state){
    $validators = array(
        'file_validate_extensions' => array('jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp csv'), // Проверка на расширения
        'file_validate_size' => array(1 * 1024 * 1024), // Проверка на размер файла (максимум 1mb)
      );
  // Загружаем файл в sites/default/files (по умолчанию)
  if ($file = file_save_upload('filedown', $validators, 'private://datafiles/calcmet')) {
    $form_state['values']['rastvorcat']['filedown'] = $file; // передаём информацию о файле в ф-ю mymodule_form_submit()
  }
  else {
    form_set_error('filedown', 'Файл не был загружен');
  }
}

function admin_cat_file_submit($form, &$form_state){
    $file = $form_state['values']['rastvorcat']['filedown'];
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
        foreach($one_row as $entry){
            //dsm($entry);
            $entrydb = array(
                'rastvorcatid' => $entry[0],   
                'rastvorid' => $entry[1],   
                'cementid' => $entry[2],   
                'cement' => $entry[3],   
                'pesok' => $entry[4],   
                'izvest' => $entry[5],   
                'voda' => $entry[6],   
            );
          //dsm($entrydb);
          $return = rastvor_entry_insert ('rastvordataset', $entrydb);
          if ($return) {
             drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entrydb, TRUE))));
           }        
        }
    }
}

function rastvor_all_union_table(){
    $header = array(
        'Вид раствора',
        'Марка (состав) раствора',
        'Марка цемента',
        'Расход цемента, т',
        'Расход песка, м3',
        'Расход извести, т',
        'Расход воды, м3',
    );
    $entries = db_select('rastvordataset', 'rd');
    $entries ->leftJoin('rastvorcat', 'rc', 'rd.rastvorcatid = rc.rastvorcatid');
    $entries ->leftJoin('rastvortype', 'rt', 'rd.rastvorid = rt.rastvorid');
    $entries ->leftJoin('rastvorcementname', 'rcm', 'rd.cementid = rcm.cementid');
    $entries -> fields('rc', array('title'));
    $entries -> fields('rt', array('title'));
    $entries -> fields('rcm', array('title'));
    $entries -> fields('rd', array('cement', 'pesok', 'izvest', 'voda'));
    $entries = $entries->execute()->fetchAll(PDO::FETCH_ASSOC);
    //dsm($entries);
    $rows = array();
    foreach($entries as $entry){
        $rows[] = array_map('check_plain', $entry);
        //$rows[] = $entry;
        //dsm($rows);
        
//        $output .= '<tr>'
//                .'<td>'.$entry->title.'</td>'
//                . '<td>'.$entry->rt_title.'</td>'
//                . '<td>'.$entry->rcm_title.'</td>'
//                . '<td>'.$entry->cement.'</td>'
//                . '<td>'.$entry->pesok.'</td>'
//                . '<td>'.$entry->izvest.'</td>'
//                . '<td>'.$entry->voda.'</td>'
//                .'</tr>';
        
    
        
    }
    
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
    
    return $output;
}