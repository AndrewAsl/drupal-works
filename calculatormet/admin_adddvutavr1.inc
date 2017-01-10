<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Prepare a simple form to add an entry, with all the textfielderesting fields.
 */
function calcmet_form_adddvutavr_1($form, &$form_state) {
  $form = array();
  
  $form['dvutavr1data'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Данные по двутаврам'),
  );
  $form['dvutavr1data']['dvutavrname'] = array(
    '#type'  => 'textfield',
    '#title' => t('Номер двутавра'),
    '#size'  => 60,
  );
  $form['dvutavr1data']['dvutavrheight'] = array(
    '#type'  => 'textfield',
    '#title' => t('Высота (h), мм'),
    '#size'  => 60,
  );
  $form['dvutavr1data']['dvutavrwidth'] = array(
    '#type'  => 'textfield',
    '#title' => t('Ширина (b), мм'),
    '#size'  => 60,
  );
  $form['dvutavr1data']['dvutavrthickness'] = array(
    '#type'  => 'textfield',
    '#title' => t('Толщина (s), мм'),
    '#size'  => 60,
  );
  $form['dvutavr1data']['dvutavrthicknesspolka'] = array(
    '#type'  => 'textfield',
    '#title' => t('Толщина полки (t), мм'),
    '#size'  => 60,
  );
  $form['dvutavr1data']['csa'] = array(
    '#type'  => 'textfield',
    '#title' => t('Площадь сечения, см2'),
    '#size'  => 60,
  );
  $form['dvutavr1data']['massonem'] = array(
    '#type'  => 'textfield',
    '#title' => t('Масса 1 м, кг'),
    '#size'  => 60,
  );
  $form['dvutavr1data']['drawonemetr'] = array(
    '#type'  => 'textfield',
    '#title' => t('Расчет площади поверхности в м2 1 кг (м2)'),
    '#size'  => 60,
  );
  
  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Add'),
  );
  return $form;
}

function calcmet_form_adddvutavr_1_submit($form, &$form_state) {  
  // Save the submitted entry.
  //dsm($form_state);  
  $basename = 'calcmetdvutavr';
  if(!empty($form_state['values']['dvutavrname'] && $form_state['values']['dvutavrheight'] && $form_state['values']['drawonemetr'])){
      $entry = array(
        'ccid'  => 3,  
        'cucid'  => 1,  
        'dvutavrname' => $form_state['values']['dvutavrname'],
        'dvutavrheight' => $form_state['values']['dvutavrheight'],
        'dvutavrwidth' => $form_state['values']['dvutavrwidth'],
        'dvutavrthickness' => $form_state['values']['dvutavrthickness'],
        'dvutavrthicknesspolka' => $form_state['values']['dvutavrthicknesspolka'],
        'csa' => $form_state['values']['csa'], 
        'massonem' => $form_state['values']['massonem'], 
        'drawonemetr' => $form_state['values']['drawonemetr'], 
      );
  } else {
      drupal_set_message ('Введите данные');
  }   
  $return = calcmet_entry_insert ($basename, $entry);
  if ($return) {
    drupal_set_message(t("Created entry @entry", array('@entry' => print_r($entry, TRUE))));
  }
}